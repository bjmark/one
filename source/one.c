#include <assert.h>
#include <stdlib.h>
#include "one.h"

one *one_new(int count){
	one *p = malloc(sizeof(one) * count);
	
	p->prev = NULL;
	
	int last = count - 1;

	for(int i = 0; i < last; i++){
		p[i].name = NULL;
		p[i].type = NULL;

		p[i].next = p + i + 1;
		p[i + 1].prev = p + i;
	}

	p[last].name = NULL;
	p[last].type = NULL;

	p[last].next = NULL;
	
	return p;
}

one *one_first(one *p){
	while(1){
		if(p->prev == NULL) return p;
		p = p->prev;
	}
}

one *one_last(one *p){
	while(1){
		if(p->next == NULL) return p;
		if(p->next->prev != p) return p;
		p = p->next;
	}
}

one one_empty(){
	return (one){.next = NULL, .prev = NULL, .name = NULL, .type = NULL};
}

one *one_parent(one *p){
	return one_last(p)->next;
}

one *one_find(one *p, char *name, char *type){
	atom name2 = one_atom(name);
	atom type2 = one_atom(type);
	do{
		if(p->name == name2 && p->type == type2)
			return p;

		p = p->next;
	}while(p != NULL);

	return p;
}

one *one_find_by_name(one *p, char *name){
	atom name2 = one_atom(name);
	do{
		if(p->name == name2)
			return p;

		p = p->next;
	}while(p != NULL);

	return p;
}


one one_call(one *p, char *name, one arg){
	return one_find(p, name, "method")->method(p, arg);
}

one *one_attach(one *one1_p, one *one2_p){
	one *last = one_last(one1_p);
	last->next = one2_p;
	
	return one1_p;
}

one *one_detach(one *one_p){
	one *last = one_last(one_p);
	last->next = NULL;

	return one_p;
}

one *one_join(one *one1_p, one *one2_p){
	one *last = one_last(one1_p);

	last->next = one2_p;
	one2_p->prev = last;

	return one1_p;
}

