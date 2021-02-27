#include <stdio.h>
#include "../source/one_assert.h"
#include "../source/one.h"

void test_one_string(void){
	printf("test_one_string\n");
	
	one *string = one_string();

	one_assert(one_find(string, "new", "method") != NULL);
	one_assert(one_find(string, "=", "method") != NULL);
	one_assert(one_find(string, "==", "method")!= NULL);
	one_assert(one_find(string, "@space_unit", "int") != NULL);
	one_assert(one_find(string, "name", "method")!= NULL);
	one_assert(one_find(string, "str", "method")!= NULL);
	one_assert(one_find(string, "respace", "method")!= NULL);
}

void test_one_string_new(void){
	printf("test_one_string_new\n");

	one *string = one_string();
	one *str = one_call(string, "new", one_empty()).one_p;
	one_assert(one_parent(str) == one_string());
	
	one *p = one_find(str, "@str", "char_p");
	one_assert(p->char_p == NULL);

	p = one_find(str, "@space", "int");
	one_assert(p->c_int == 0);

	one_assert(one_parent(p) == one_string());
}

void test_one_string_respace(void){
	printf("test_one_string_respace\n");
	
	one *p = one_call(one_string(), "new", one_empty()).one_p;
	one_call(p, "respace", (one){.c_int = 100});
	one_assert(one_find_by_name(p, "@space")->c_int == 1024); 

	one_call(p, "respace", (one){.c_int = 1000});
	one_assert(one_find_by_name(p, "@space")->c_int == 1024); 
	
	one_call(p, "respace", (one){.c_int = 1024});
	one_assert(one_find_by_name(p, "@space")->c_int == 2048); 
}

void test_one_string_assign(void){
	printf("test_one_string_assign\n");
	
	one *p = one_call(one_string(), "new", one_empty()).one_p;
	one_call(p, "=", (one){.char_p = "abc"});

	one_assert(one_find_by_name(p, "@space")->c_int == 1024);


	one *p2 = one_call(one_string(), "new", one_empty()).one_p;
	one_call(p2, "=", *p);

	//one_assert(one_call(p, "==", *p2).c_int == 0);
}

void test_one_string_cmp(void){
	printf("test_one_string_cmp\n");

	one *p = one_call(one_string(), "new", one_empty()).one_p;
	one_call(p, "=", (one){.char_p = "abc"});

	one_assert(one_call(p, "==", (one){.char_p = "abc"}).c_int == 0);
	one_assert(one_call(p, "==", (one){.char_p = "abcd"}).c_int != 0);
	
	one_assert(one_call(p, "==", *p).c_int == 0);
}

void test_one_string_name(void){
	printf("test_one_string_name\n");

	one *string = one_string();
	one_assert(one_call(string, "name", one_empty()).char_p == one_atom("string"));

	one *s = one_call(string, "new", one_empty()).one_p;
	one_assert(one_call(s, "name", one_empty()).char_p == one_atom("string"));
}

void test_one_string_str(void){
	printf("test_one_string_str\n");
	
	one *str = one_call(one_string(), "new", one_empty()).one_p;
	one_assert(one_call(str, "str", *str).char_p == one_find_by_name(str, "@str")->char_p);

	one str2 = {.char_p = "abc"};
	one_assert(one_call(str, "str", str2).char_p == str2.char_p);
}

int main(void){
	printf("start testing...\n\n");

	one_test_success(test_one_string);
	one_test_success(test_one_string_new);
	one_test_success(test_one_string_cmp);
	one_test_success(test_one_string_name);
	one_test_success(test_one_string_respace);
	one_test_success(test_one_string_assign);
	one_test_success(test_one_string_str);

	printf("test end\n");

	return 1;
}

