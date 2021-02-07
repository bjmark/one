#include <stdlib.h>
#include "one.h"

one *one_new(int count){
	one *one_p = malloc(sizeof(one) * count);
	
	one_p->prev = NULL;
	
	int last = count - 1;

	for(int i = 0; i < last; i++){
		one_p[i].next = one_p + i + 1;
		one_p[i + 1].prev = one_p + i;
	}

	one_p[last].next = NULL;
	
	return one_p;
}

