typedef char * atom;

atom one_atom(char *name);

typedef struct one one;

struct one{
	atom name;
	atom type;
	
	union{
		int _int;
		char *char_p;
		void *void_p;
		one *one_p;
	};

	one *prev;
	one *next;
};

one *one_new(int count);
one *one_last(one *p);
one one_empty();
one *one_parent(one *p);
