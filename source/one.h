typedef char * atom;

atom one_atom(char *name);

typedef struct one one;

typedef one (*one_method)(one *self, one arg);

struct one{
	atom name;
	atom type;
	
	union{
		int c_int;
		char *char_p;
		void *void_p;
		one *one_p;
		one_method method;
	};

	one *prev;
	one *next;
};


one *one_new(int count);

one *one_first(one *p);
one *one_last(one *p);

one one_empty();
one *one_parent(one *p);

one *one_find(one *p, char *name, char *type);
one *one_find_by_name(one *p, char *name);

one one_call(one *p, char *name, one arg);

one *one_attach(one *p1, one *p2);

one *one_detach(one *p);

one *one_join(one *p1, one *p2);

one *one_string(void);

one *one_array(void);
