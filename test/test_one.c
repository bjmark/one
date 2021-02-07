#include <assert.h>
#include <stdio.h>
#include "../source/one.h"

void test_one_new(void){
	printf("test_one_new\n");

	one *one_p = one_new(1);
	assert(one_p != NULL);
	assert(one_p->prev == NULL);
	assert(one_p->next == NULL);

	one_p = one_new(3);

	assert(one_p->prev == NULL);
	
	int i = 1;
	
	while(one_p->next != NULL){
		one_p = one_p->next;
		i++;
	}

	assert(i == 3);
	
	i = 1;
	while(one_p->prev != NULL){
		one_p = one_p->prev;
		i++;
	}

	assert(i == 3);
}

void test_one_last(void){
	printf("test_one_last\n");

	one one1 = {.next = NULL, .prev = NULL};
	assert(one_last(&one1) == &one1);

	one one2 = {.next = NULL, .prev = &one1};
	one1.next = &one2;
	
	assert(one_last(&one1) == &one2);
}

void test_one_empty(){
	printf("test_one_empty\n");
	
	one one1 = one_empty();
	assert(one1.next == NULL);
	assert(one1.prev == NULL);
}

void test_one_parent(void){
	printf("test_one_parent\n");

	one one1 = one_empty();
	assert(one_parent(&one1) == NULL);

	one one2 = one_empty();
	one1.next = &one2;

	assert(one_parent(&one1) == &one2);
}

int main(void){
	printf("start testing...\n");
	test_one_new();
	test_one_last();
	test_one_empty();
	test_one_parent();
	printf("test end\n");
	return 1;
}
