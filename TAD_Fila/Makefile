all: paciente.o fila.o testes.o 
	gcc paciente.o fila.o testes.o -o testes -std=c99 -Wall -lm

verifica: paciente.o fila.o testes.o 
	gcc -g -fsanitize=address paciente.o fila.o testes.o -o testes -std=c99 -Wall -lm

paciente.o: 
	gcc -c ../TAD_Paciente/paciente.c 

testes.o:
	gcc -c testes.c

fila.o:
	gcc -c fila.c

make run:
	./testes

clean:
	rm paciente.o
	rm fila.o
	rm testes.o
	rm testes
