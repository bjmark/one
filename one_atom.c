typedef *void atom;

struct element{
    char *name;
    struct element *next;
};

static struct element *hash_table[1024];

atom one_atom(char *name){
    static struct element **hash_table = NULL;
    if(hash_table == NULL){
        hash_table = malloc(sizeof(element) * 1024);
        for(int i = 0; i < 1024; i++)
            hash_talbe[0] = NULL;
    }

    int hash_code = 0;
    for(int i = 0; i < 16; i++){
        hash_code += name[i];
        if(name[i] == '\0') break;
    }

    hash_code %= 1024;

}
