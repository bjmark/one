#include <stdlib.h>
#include <string.h>
#include "one.h"

static one one_string_new(one *self, one arg){
	one *p = one_new(1);
	
	p->name = one_atom("@str");
	p->type = one_atom("char_p");
	p->char_p = NULL;

	p->next = one_new(1);
	p->next->prev = p;
	
	p = p->next;
	p->name = one_atom("@len");
	p->type = one_atom("int");
	p->c_int = 0;

	p->next = one_new(1);
	p->next->prev = p;

	p = p->next;
	p->name = one_atom("@space");
	p->type = one_atom("int");
	p->c_int = 0;

	one_attach(p, self);

	return (one){.one_p = one_first(p)};
}

static one one_string_assign(one *self, one arg){
	int len = strlen(arg.char_p);
	int unit = 1024;
	
	int new_space = (len / unit + 1) * 1024;

	one *attr_space = one_find_by_name(self, "@space");
	one *attr_str = one_find_by_name(self, "@str");

	if(new_space > attr_space->c_int){
		if(attr_space->c_int > 0) free(attr_str->char_p);
		attr_str->char_p = malloc(new_space);
		attr_space->c_int = new_space;
	}
	
	strcpy(attr_str->char_p, arg.char_p);
	one_find_by_name(self, "@len")->c_int = len;

	return *self;
}

static one one_string_equal(one *self, one arg){
	one *p = one_find_by_name(&arg, "@str");
	
	char *str = (p == NULL ? NULL : p->char_p);
	
	if(str == NULL) str = arg.char_p;

	int i = strcmp(one_find_by_name(self, "@str")->char_p, str);
	
	return (one){.c_int = i};
}

one *one_string(void){
	static one *string = NULL;
	
	if(string != NULL) return string;

	one *p = one_new(1);
	
	p->name = one_atom("new");
	p->type = one_atom("method");
	p->method = one_string_new; 

	p->next = one_new(1);
	p->next->prev = p;
	p = p->next;

	p->name = one_atom("=");
	p->type = one_atom("method");
	p->method = one_string_assign;

	p->next = one_new(1);
	p->next->prev = p;
	p = p->next;

	p->name = one_atom("==");
	p->type = one_atom("method");
	p->method = one_string_equal;

	string = one_first(p);
	return string;
}
