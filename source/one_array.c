#include <stdlib.h>
#include <stdio.h>
#include "one.h"

static one one_array_new(one *self, one arg){
	one *p = one_new(1);

	p->name = one_atom("@col");
	p->type = one_atom("int");
	p->c_int = one_find_by_name(self, "@col")->c_int;

	one_join(p, one_new(1));
	p = one_last(p);

	p->name = one_atom("@row");
	p->type = one_atom("int");
	p->c_int = 0;

	one_join(p, one_new(1));
	p = one_last(p);

	p->name = one_atom("@len");
	p->type = one_atom("int");
	p->c_int = 0;

	one_join(p, one_new(1));
	p = one_last(p);

	p->name = one_atom("@first_row");
	p->type = one_atom("void_p");
	p->void_p = NULL;

	one_attach(p, self);

	return (one){.one_p = one_first(p)};
}

one one_array_respace(one *self, one arg){
	one *col = one_find_by_name(self, "@col");
	one *row = one_find_by_name(self, "@row");
	one *first_row = one_find_by_name(self, "@first_row");

	int space = row->c_int * col->c_int;
	if(space >= arg.c_int) return *self;

	int row2 = arg.c_int / col->c_int;
	if(arg.c_int % col->c_int != 0 ) row2++;

	one ***p = malloc(row2 * sizeof(***p));

	int i;
	for(i = 0; i < row->c_int; i++){
		p[i] = (one **)first_row->void_p + i;
	}

	for(; i < row2; i++){
		p[i] = malloc(col->c_int * sizeof(one **));
	}

	first_row->void_p = p;
	row->c_int = row2;

	return *self;
}

one *one_array(void){
	static one *array = NULL;

	if(array != NULL) return array;

	one *p = one_new(1);
	
	p->name = one_atom("new");
	p->type = one_atom("method");
	p->method = one_array_new; 

	one_join(p, one_new(1));
	p = one_last(p);

	p->name = one_atom("@col");
	p->type = one_atom("int");
	p->c_int = 128;

	one_join(p, one_new(1));
	p = one_last(p);

	p->name = one_atom("respace");
	p->type = one_atom("method");
	p->method = one_array_respace; 

	array = one_first(p);
	return array;
}
