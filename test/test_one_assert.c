#include <stdio.h>
#include "../source/one_assert.h"

void success(void){
	printf("test1\n");
	one_assert(1 == 1);
}

void fail(void){
	printf("test2\n");
	one_assert(1 == 2);
}

int main(void){
	one_test_success(success);
	one_test_success(fail);
}
