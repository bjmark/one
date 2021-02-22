#include <stdio.h>
#include "../source/one_assert.h"

void success(void){
	printf("test1\n");
	one_assert(1 == 1);
	one_assert(2 == 2);
}

void fail(void){
	printf("test2\n");
	one_assert(1 == 2);
	one_assert(2 == 2);
}

int main(void){
	one_test_success(success);
	one_test_success(fail);

	one_test_fail(fail);
	one_test_fail(success);
}
