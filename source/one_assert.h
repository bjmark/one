#define one_assert(x) if((x) == 0) one_fail()(__FILE__, __LINE__, __func__, #x)

typedef void (*one_fail_func)(char *file, int line, const char *func, char *exp);

one_fail_func one_fail(void);

void one_set_fail(one_fail_func arg);

one_fail_func one_fail(void);

void one_test_success(void (*)(void));

void one_test_fail(void (*)(void));
