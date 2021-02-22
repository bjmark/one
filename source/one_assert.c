#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "one_assert.h"

#define handle_error_en(en, msg) \
	do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

struct retval {
	char success;
	char *file;
	int line;
	char *func;
	char *exp;
};

static void fail0(char *file, int line, const char *func, char *exp){
	struct retval *retval = malloc(sizeof(*retval));

	retval->success = 'n';
	retval->file = strdup(file);
	retval->line = line;
	retval->func = strdup(func);
	retval->exp = strdup(exp);

	pthread_exit(retval);
	//printf("%s: %d: %s: `one_assert(%s)` failed\n", file, line, func, exp);
}

static one_fail_func func = fail0;

void one_set_fail(one_fail_func arg){
	func = arg;
}

one_fail_func one_fail(void){
	return func;
}

static void * worker (void *p){
	void (*p2)(void) = p;
	p2();

	struct retval *retval = malloc(sizeof(*retval));
	retval->success = 'y';
	pthread_exit(retval);
}

static void *one_test(void (*func)(void)){
	pthread_attr_t attr;

	int n;
	n = pthread_attr_init(&attr);
	if(n != 0)
		handle_error_en(n, "pthread_attr_init");

    n = pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
    if(n != 0)
		handle_error_en(n, "pthread_attr_setdetachstate");

	pthread_t thread;   
	
	n = pthread_create(&thread, &attr, worker, func);
	if (n != 0)
		handle_error_en(n, "pthread_create");

	n = pthread_attr_destroy(&attr);
	if(n != 0)
		handle_error_en(n, "pthread_attr_destroy");

	void *res;
	n = pthread_join(thread, &res);
	if (n != 0)
		handle_error_en(n, "pthread_join");

	return res;
}

void one_test_success(void (*func)(void)){
	struct retval *retval = one_test(func);

	if(retval->success == 'y'){
		printf("success\n\n");
		
		free(retval);
	}else{
		printf("%s: %d: %s: `one_assert(%s)` failed\n", retval->file, retval->line, retval->func, retval->exp);
		
		free(retval->file);
		free(retval->func);
		free(retval->exp);
		free(retval);
	}
}

void one_test_fail(void (*func)(void)){
	struct retval *retval = one_test(func);

	if(retval->success == 'n'){
		printf("success\n\n");
	}else{
		printf("fail\n");
	}

	free(retval->file);
	free(retval->func);
	free(retval->exp);
	free(retval);
}
