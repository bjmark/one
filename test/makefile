objects = test_one.o one.o one_atom.o one_assert.o

test_one: $(objects)
	gcc -pthread -o test_one $(objects)

test_one.o: test_one.c ../source/one.h ../source/one_assert.h
	gcc -c test_one.c

one.o: ../source/one.c ../source/one.h
	gcc -c ../source/one.c

test_one_atom: test_one_atom.o one_atom.o one_assert.o
	gcc -pthread -o test_one_atom test_one_atom.o one_atom.o one_assert.o

test_one_atom.o: test_one_atom.c ../source/one.h ../source/one_assert.h
	gcc -c test_one_atom.c

one_atom.o: ../source/one_atom.c ../source/one.h
	gcc -c ../source/one_atom.c

one_assert.o: ../source/one_assert.c ../source/one_assert.h
	gcc -pthread -c ../source/one_assert.c

test_one_assert.o: test_one_assert.c ../source/one_assert.h
	gcc -c test_one_assert.c

test_one_assert: test_one_assert.o one_assert.o
	gcc -pthread -o test_one_assert test_one_assert.o one_assert.o

one_string.o: ../source/one_string.c ../source/one.h ../source/one_assert.h
	gcc -c ../source/one_string.c

test_one_string.o: test_one_string.c ../source/one_assert.h ../source/one.h
	gcc -c test_one_string.c

test_one_string: test_one_string.o one_string.o one.o one_assert.o one_atom.o
	gcc -pthread -o test_one_string test_one_string.o one_string.o one.o one_assert.o one_atom.o

one_array.o: ../source/one_array.c ../source/one.h ../source/one_assert.h
	gcc -c ../source/one_array.c

test_one_array.o: test_one_array.c ../source/one_assert.h ../source/one.h
	gcc -c test_one_array.c

test_one_array: test_one_array.o one_array.o one.o one_assert.o one_atom.o
	gcc -pthread -o test_one_array test_one_array.o one_array.o one.o one_assert.o one_atom.o

one_basic.o: ../source/one_basic.c ../source/one.h
	gcc -c ../source/one_basic.c

test_one_basic.o: test_one_basic.c ../source/one.h ../source/one_assert.h
	gcc -c test_one_basic.c

test_one_basic: test_one_basic.o one_basic.o one.o one_assert.o one_atom.o
	gcc -pthread -o test_one_basic test_one_basic.o one_basic.o one.o one_assert.o one_atom.o

clean:
	rm *.o
