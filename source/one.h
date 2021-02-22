typedef char * atom;

atom one_atom(char *name);

typedef struct one one;

typedef one (*one_method)(one *self, one arg);

struct one{
	atom name;
	atom type;
	
	union{
		int _int;
		char *char_p;
		void *void_p;
		one *one_p;
		one_method method;
	};

	one *prev;
	one *next;
};


one *one_new(int count);
one *one_last(one *p);
one one_empty();
one *one_parent(one *p);

one *one_find(one *one_p, atom name, atom type);
one *one_find_0(one *one_p, atom name);

one one_call(one *one_p, char *name, one arg);

one *one_attach(one *one1_p, one *one2_p);
