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

int main(void){
	printf("start testing...\n");
	test_one_new();
	printf("test end\n");
	return 1;
}
