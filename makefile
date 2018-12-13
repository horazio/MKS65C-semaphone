make: sem.c swag.h
	gcc -o Sem sem.c

run: Sem sem.c
	./Sem
