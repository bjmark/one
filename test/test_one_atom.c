#include <assert.h>
#include <stdio.h>
#include "../source/one.h"

int main(void){
	atom a = one_atom("abc");
	atom b = one_atom("abc");
	assert(a == b);

	atom c = one_atom("123");
	assert(a != c);

	atom d = one_atom("123");
	assert(c = d);
}

