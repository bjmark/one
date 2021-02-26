#include <stdlib.h>
#include <string.h>
#include "one.h"

static one one_string_new(one *self, one arg){
	one *p = one_new(1);
	
	p->name = one_atom("@str");
	p->type = one_atom("char_p");
	p->char_p = NULL;

	one_join(p, one_new(1));
	p = one_last(p);

	p->name = one_atom("@space");
	p->type = one_atom("int");
	p->c_int = 0;
	
	one_join(p, one_new(1));
	p = one_last(p);

	one_attach(p, self);

	return (one){.one_p = one_first(p)};
}

static one one_string_assign(one *self, one arg){
	int len = strlen(arg.char_p);
	int unit = one_find_by_name(self, "@space_unit")->c_int;
	
	int new_space = (len / unit + 1) * 1024;

	one *attr_space = one_find_by_name(self, "@space");
	one *attr_str = one_find_by_name(self, "@str");

	if(new_space > attr_space->c_int){
		if(attr_space->c_int > 0) free(attr_str->char_p);
		attr_str->char_p = malloc(new_space);
		attr_space->c_int = new_space;
	}
	
	strcpy(attr_str->char_p, arg.char_p);

	return *self;
}

static one one_string_equal(one *self, one arg){
	one *p = one_find_by_name(&arg, "@str");
	
	char *str = (p == NULL ? NULL : p->char_p);
	
	if(str == NULL) str = arg.char_p;

	int i = strcmp(one_find_by_name(self, "@str")->char_p, str);
	
	return (one){.c_int = i};
}

static one one_string_append(one *self, one arg){
	return *self;
}

one *one_string(void){
	static one *string = NULL;
	
	if(string != NULL) return string;

	one *p = one_new(1);
	
	p->name = one_atom("new");
	p->type = one_atom("method");
	p->method = one_string_new; 

	one_join(p, one_new(1));
	p = one_last(p);

	p->name = one_atom("=");
	p->type = one_atom("method");
	p->method = one_string_assign;

	one_join(p, one_new(1));
	p = one_last(p);

	p->name = one_atom("==");
	p->type = one_atom("method");
	p->method = one_string_equal;

	one_join(p, one_new(1));
	p = one_last(p);

	p->name = one_atom("@space_unit");
	p->type = one_atom("int");
	p->c_int = 1024;

	string = one_first(p);
	return string;
}
