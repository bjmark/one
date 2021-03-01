#include <stdio.h>
#include "../source/one_assert.h"
#include "../source/one.h"

void test_one_array(void){
	printf("test_one_array\n");
	
	one *p = one_array();
	
	one_assert(one_find(p, "new", "method") != NULL);
}

int main(void){
	printf("start testing...\n\n");
	
	one_test_success(test_one_array);

	printf("test end\n");
	return 1;
}
