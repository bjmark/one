#include <stdlib.h>
#include "one.h"

static one one_basic_is_empty(one *self, one arg){
	one *p = one_find(self, "@empty", "int");
	return p == NULL ? (one){.c_int = 0} : *p;
}

one *one_basic(void){
	static one *basic = NULL;
	
	if(basic != NULL) return basic;

	one *p = one_new(1);

	p->name = one_atom("is_empty?");
	p->type = one_atom("method");
	p->method = one_basic_is_empty;

	basic = one_first(p);
	return basic;
}
