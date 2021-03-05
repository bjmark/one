#include <stdio.h>
#include "../source/one.h"
#include "../source/one_assert.h"

void test_one_basic(void){
	printf("test_one_basic\n");

	one *p = one_basic();
	one_assert(one_find(p, "is_empty?", "method") != NULL);
}

void test_one_basic_is_empty(void){
	printf("test_one_basic_is_empty\n");

	one *p = one_basic();
	one_assert(one_call(p, "is_empty?", one_empty()).c_int == 0);
}

int main(void){
	printf("start testing...\n\n");

	one_test_success(test_one_basic);

	printf("test end\n");
}
