#include <assert.h>
#include <stdio.h>
#include "../source/one.h"
#include "../source/one_assert.h"

void test_one_atom(void){
	printf("test_one_atom\n");
	
	atom a = one_atom("abc");
	atom b = one_atom("abc");
	one_assert(a == b);

	atom c = one_atom("123");
	one_assert(a != c);

	atom d = one_atom("123");
	one_assert(c = d);
}

int main(void){
	printf("start testing...\n\n");
	
	one_test_success(test_one_atom);

	printf("test end\n");
	return 1;
}

