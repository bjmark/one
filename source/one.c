#include <assert.h>
#include <stdlib.h>
#include "one.h"

//one one_error(){
//}

one *one_new(int count){
	one *one_p = malloc(sizeof(one) * count);
	
	one_p->prev = NULL;
	
	int last = count - 1;

	for(int i = 0; i < last; i++){
		one_p[i].name = NULL;
		one_p[i].type = NULL;

		one_p[i].next = one_p + i + 1;
		one_p[i + 1].prev = one_p + i;
	}

	one_p[last].name = NULL;
	one_p[last].type = NULL;

	one_p[last].next = NULL;
	
	return one_p;
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

one *one_find(one *one_p, char *name, char *type){
	atom name2 = one_atom(name);
	atom type2 = one_atom(type);
	do{
		if(one_p->name == name2 && one_p->type == type2)
			return one_p;

		one_p = one_p->next;
	}while(one_p != NULL);

	return one_p;
}

one *one_find_0(one *one_p, char *name){
	atom name2 = one_atom(name);
	do{
		if(one_p->name == name2)
			return one_p;

		one_p = one_p->next;
	}while(one_p != NULL);

	return one_p;
}


one one_call(one *one_p, char *name, one arg){
	one *one1_p = one_find(one_p, name, "method");
	assert(one1_p != NULL);
	return one1_p->method(one_p, arg);
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

