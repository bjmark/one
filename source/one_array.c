#include <stdlib.h>
#include <stdio.h>
#include "one.h"
#include "one_assert.h"

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

one one_array_append(one *self, one arg){
	one *len = one_find_by_name(self, "@len");

	one_call(self, "respace", (one){.c_int = len->c_int + 1});
	
	one *col = one_find_by_name(self, "@col");
	
	int row2 = len->c_int / col->c_int;
	int col2 = len->c_int % col->c_int;

	one *first_row = one_find_by_name(self, "@first_row");
	one ***p = first_row->void_p;
	p[row2][col2] = arg.one_p;

	len->c_int++;

	return *self;
}

one one_array_index(one *self, one arg){
	one *len = one_find_by_name(self, "@len");
	
	one_assert(arg.c_int < len->c_int);
	one_assert(arg.c_int >= 0);

	one *col = one_find_by_name(self, "@col");
	int row2 = arg.c_int / col->c_int;
	int col2 = arg.c_int % col->c_int;
	
	one *first_row = one_find_by_name(self, "@first_row");
	one ***p = first_row->void_p;

	return (one){.one_p = p[row2][col2]};
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

	one_join(p, one_new(1));
	p = one_last(p);

	p->name = one_atom("<<");
	p->type = one_atom("method");
	p->method = one_array_append; 

	one_join(p, one_new(1));
	p = one_last(p);

	p->name = one_atom("[]");
	p->type = one_atom("method");
	p->method = one_array_index; 
	
	array = one_first(p);
	return array;
}
