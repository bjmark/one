#include <stdio.h>
#include "../source/one_assert.h"
#include "../source/one.h"

void test_one_array(void){
	printf("test_one_array\n");
	
	one *p = one_array();
	
	one_assert(one_find(p, "new", "method") != NULL);
	one_assert(one_find(p, "@col", "int") != NULL);
	one_assert(one_find(p, "respace", "method") != NULL);
	one_assert(one_find(p, "<<", "method") != NULL);
	one_assert(one_find(p, "[]", "method") != NULL);
}

void test_one_array_new(void){
	printf("test_one_array_new\n");

	one *p = one_call(one_array(), "new", one_empty()).one_p;

	one_assert(one_find_by_name(p, "@col")->c_int == one_find_by_name(one_array(), "@col")->c_int);
	one_assert(one_find_by_name(p, "@row")->c_int == 0);
	one_assert(one_find_by_name(p, "@len")->c_int == 0);
	one_assert(one_find_by_name(p, "@first_row")->void_p == NULL);
}

void test_one_array_respace(void){
	printf("test_one_array_respace\n");

	one *p = one_call(one_array(), "new", one_empty()).one_p;

	one_call(p, "respace", (one){.c_int = 1});
	one_assert(one_find_by_name(p, "@row")->c_int == 1);

	one_call(p, "respace", (one){.c_int = 100});
	one_assert(one_find_by_name(p, "@row")->c_int == 1);
	
	one_call(p, "respace", (one){.c_int = 128});
	one_assert(one_find_by_name(p, "@row")->c_int == 1);
	
	one_call(p, "respace", (one){.c_int = 128 + 1});
	one_assert(one_find_by_name(p, "@row")->c_int == 2);

	one *p2 = one_find_by_name(p, "@first_row");
	one ***p3 = p2->void_p;
	p3[0][0] = p2;
	p3[1][1] = p2;
}

void test_one_array_append(void){
	printf("test_one_array_append\n");

	one *p = one_call(one_array(), "new", one_empty()).one_p;
	
	one one1;
	one_call(p, "<<", (one){.one_p = &one1});

	one ***p2 = one_find_by_name(p, "@first_row")->void_p;

	one_assert(p2[0][0] == &one1);
	
	one one2;
	one_call(p, "<<", (one){.one_p = &one2});

	one_assert(p2[0][1] == &one2);

	one *p3;

	for(int i = 0; i < 128; i++){
		p3 = one_new(1);
		p3->c_int = i;
		one_call(p, "<<", (one){.one_p = p3});

	}

	p2 = one_find_by_name(p, "@first_row")->void_p;
	
	one_assert(p2[1][0]->c_int == 126);
	one_assert(p2[1][1]->c_int == 127);

}

void test_one_array_index(void){
	printf("test_one_array_index\n");

	one *p = one_call(one_array(), "new", one_empty()).one_p;

	one one1;

	one_call(p, "<<", (one){.one_p = &one1});

	one_assert(one_call(p, "[]", (one){.c_int = 0}).one_p == &one1);
}

void test_one_array_index2(void){
	printf("test_one_array_index2\n");
	
	one *p = one_call(one_array(), "new", one_empty()).one_p;
	one_call(p, "[]", (one){.c_int = 1});
}

void test_one_array_index3(void){
	printf("test_one_array_index3\n");
	
	one *p = one_call(one_array(), "new", one_empty()).one_p;
	one_call(p, "[]", (one){.c_int = -1});
}

int main(void){
	printf("start testing...\n\n");
	
	one_test_success(test_one_array);
	one_test_success(test_one_array_new);
	one_test_success(test_one_array_respace);
	one_test_success(test_one_array_append);

	one_test_success(test_one_array_index);
	one_test_fail(test_one_array_index2);
	one_test_fail(test_one_array_index3);

	printf("test end\n");
	return 1;
}
