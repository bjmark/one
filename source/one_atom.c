#include <string.h>
#include <stdlib.h>
#include "one.h"

struct element{
    char *name;
    struct element *next;
};

static struct element *new_element(char *name){
    struct element *p;

    p =  malloc(sizeof(struct element));
    p->name = malloc(strlen(name) + 1);
    strcpy(p->name, name);
    p->next = NULL;

    return p;
}

atom one_atom(char *name){
    static struct element **hash_table = NULL;

    if(hash_table == NULL){
        hash_table = malloc(sizeof(struct element *) * 1024);
        for(int i = 0; i < 1024; i++)
            hash_table[i] = NULL;
    }

    int hash_code = 0;
    for(int i = 0; i < 16; i++){
        hash_code += name[i];
        if(name[i] == '\0') break;
    }

    hash_code %= 1024;

    struct element *p = hash_table[hash_code];

    if(p == NULL){
        p = new_element(name);
        return p->name;
    }

    struct element *prev;
    do{
        if(strcmp(name, p->name) == 0) return p->name;
        prev = p;
        p = p->next;
    }while(p != NULL);

    prev->next = new_element(name);
    return prev->next->name;
}
