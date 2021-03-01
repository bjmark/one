#include <stdlib.h>
#include "one.h"

static one one_array_new(one *self, one arg){
	return *self;
}

one *one_array(void){
	static one *array = NULL;

	if(array != NULL) return array;

	one *p = one_new(1);
	
	p->name = one_atom("new");
	p->type = one_atom("method");
	p->method = one_array_new; 

	array = one_first(p);
	return array;
}
