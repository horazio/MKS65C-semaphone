make: sem.c swag.h play.c
	gcc -o Write play.c
	gcc -o Sem sem.c

run: 
	./Write

setup: 
	./Sem

clean: Write Sem 
	rm Write
	rm Sem
	rm swag.txt