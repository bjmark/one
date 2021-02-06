typedef *void atom;

struct element{
    char *name;
    struct element *next;
};

static struct element *hash_table[1024];

atom one_atom(char *name){
    int hash_code = 0;
    for(int i = 0; i < 16; i++){
        hash_code += char[i];
        if(char[i] == '\0') break;
    }

    hash_code %= 1024;
}
