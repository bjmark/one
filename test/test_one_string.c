#include <stdio.h>
#include "../source/one_assert.h"
#include "../source/one.h"

void test_one_string_new(void){
	printf("test_one_string_new\n");

	one *string = one_string();
	one *str = one_call(string, "new", one_empty()).one_p;
	one_assert(one_parent(str) == one_string());
	
	one *p = one_find(str, "@str", "char_p");
	one_assert(p->char_p == NULL);

	p = one_find(str, "@len", "int");
	one_assert(p->c_int == 0);

	p = one_find(str, "@space", "int");
	one_assert(p->c_int == 0);

	one_assert(one_parent(p) == one_string());
}

void test_one_string_assign(void){
	printf("test_one_string_assign\n");
	
	one *p = one_call(one_string(), "new", one_empty()).one_p;
	one_call(p, "=", (one){.char_p = "abc"});

	one_assert(one_find_by_name(p, "@len")->c_int == 3);
	one_assert(one_find_by_name(p, "@space")->c_int == 1024);


	one *p2 = one_call(one_string(), "new", one_empty()).one_p;
	one_call(p2, "=", *p);
	one_assert(one_find_by_name(p2, "@len")->c_int == 3);

	one_assert(one_call(p, "==", *p2).c_int == 0);
}

void test_one_string_equal(void){
	printf("test_one_string_equal\n");

	one *p = one_call(one_string(), "new", one_empty()).one_p;
	one_call(p, "=", (one){.char_p = "abc"});

	one_assert(one_call(p, "==", (one){.char_p = "abc"}).c_int == 0);
	one_assert(one_call(p, "==", (one){.char_p = "abcd"}).c_int != 0);
	
	one_assert(one_call(p, "==", *p).c_int == 0);
}

int main(void){
	printf("start testing...\n\n");

	one_test_success(test_one_string_new);
	one_test_success(test_one_string_assign);
	one_test_success(test_one_string_equal);

	printf("test end\n");

	return 1;
}

