all: paciente.o testes.o
	gcc paciente.o testes.o -o testes -std=c99 -Wall -lm

verifica: paciente.o testes.o 
	gcc -g -fsanitize=address paciente.o testes.o -o testes -std=c99 -Wall -lm

paciente.o: 
	gcc -c paciente.c

testes.o:
	gcc -c testes.c

make run:
	./testes

clean:
	
	rm paciente.o
	rm testes.o
	rm testes