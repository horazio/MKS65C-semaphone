make: sem.c swag.h play.c
	gcc -o Write play.c
	gcc -o Sem sem.c

run: Write
	./Write

setup: Sem
	./Sem