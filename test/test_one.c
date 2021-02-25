#include <stdio.h>
#include <stdlib.h>
#include "../source/one.h"
#include "../source/one_assert.h"

void test_one_new(void){
	printf("test_one_new\n");

	one *one_p = one_new(1);
	one_assert(one_p != NULL);
	one_assert(one_p->prev == NULL);
	one_assert(one_p->next == NULL);
	free(one_p);

	one_p = one_new(3);

	one_assert(one_p->prev == NULL);
	
	int i = 1;
	
	while(one_p->next != NULL){
		one_p = one_p->next;
		i++;
	}

	one_assert(i == 3);
	
	i = 1;
	while(one_p->prev != NULL){
		one_p = one_p->prev;
		i++;
	}

	one_assert(i == 3);

	free(one_p);
}

void test_one_first(void){
	printf("test_one_first\n");

	one *first, *p = one_new(3);
	
	first = p;
	one_assert(one_first(p) == first);

	one_assert(one_first(one_last(p)) == first);
}

void test_one_last(void){
	printf("test_one_last\n");

	one one1 = {.next = NULL, .prev = NULL};
	one_assert(one_last(&one1) == &one1);

	one one2 = {.next = NULL, .prev = &one1};
	one1.next = &one2;
	
	one_assert(one_last(&one1) == &one2);

	one2.prev = NULL;
	one_assert(one_last(&one1) == &one1);
}

void test_one_empty(){
	printf("test_one_empty\n");
	
	one one1 = one_empty();
	one_assert(one1.next == NULL);
	one_assert(one1.prev == NULL);
	one_assert(one1.name == NULL);
	one_assert(one1.type == NULL);
}

void test_one_parent(void){
	printf("test_one_parent\n");

	one one1 = one_empty();
	one_assert(one_parent(&one1) == NULL);

	one one2 = one_empty();
	one1.next = &one2;

	one_assert(one_parent(&one1) == &one2);
}

void test_one_find(void){
	printf("test_one_find\n");

	one one1 = one_empty();
	one1.name = one_atom("abc");
	one1.type = one_atom("char_p");

	one_assert(one_find(&one1, "abc", "char_p") != NULL);

	one one2 = one_empty();
	one2.name = one_atom("efg");
	one1.next = &one2;

	one_assert(one_find(&one1, "efg", "char_p") == NULL);
}

void test_one_find_by_name(void){
	printf("test_one_find_0\n");

	one one1 = one_empty();
	one1.name = one_atom("abc");

	one_assert(one_find_by_name(&one1, "abc") != NULL);

	one one2 = one_empty();
	one2.name = one_atom("efg");
	one1.next = &one2;

	one_assert(one_find_by_name(&one1, "efg") != NULL);
	one_assert(one_find_by_name(&one1, "efgh") == NULL);
}

one one_fun(one *self, one arg){
	return arg;
}

void test_one_call(void){
	printf("test_one_call\n");

	one one1 = one_empty();
	
	one1.name = one_atom("fun");
	one1.type = one_atom("method");
	one1.method = one_fun;

	one arg1 = {.c_int = 1};

	one_assert(one_call(&one1, "fun", arg1).c_int == 1);
}

void test_one_attach(void){
	printf("test_one_attach\n");

	one one1 = one_empty();
	one one2 = one_empty();

	one_attach(&one1, &one2);
	one_assert(one_parent(&one1) == &one2);
}

void test_one_detach(void){
	printf("test_one_detach\n");

	one one1 = one_empty();
	one one2 = one_empty();

	one_attach(&one1, &one2);
	one_assert(one_parent(&one1) == &one2);

	one_detach(&one1);
	one_assert(one_parent(&one1) == NULL);
}

void test_one_join(void){
	printf("test_one_join\n");

	one *one1_p = one_new(2);
	one *one2_p = one_new(3);

	one_join(one1_p, one2_p);

	one_assert(one_last(one1_p) == one_last(one2_p));
}

int main(void){
	printf("start testing...\n\n");
	
	//test_one_new();
	one_test_success(test_one_new);

	//test_one_first();
	one_test_success(test_one_first);

	//test_one_last();
	one_test_success(test_one_last);

	//test_one_empty();
	one_test_success(test_one_empty);

	//test_one_parent();
	one_test_success(test_one_parent);

	//test_one_find();
	one_test_success(test_one_find);

	//test_one_find_0()
	one_test_success(test_one_find_by_name);

	//test_one_call();
	one_test_success(test_one_call);

	//test_one_attach();
	one_test_success(test_one_attach);

	//test_one_detach();
	one_test_success(test_one_detach);

    //test_one_join()
	one_test_success(test_one_join);

	printf("test end\n");
	return 1;
}
