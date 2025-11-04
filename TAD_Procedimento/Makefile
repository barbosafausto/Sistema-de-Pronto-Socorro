all: procedimento.o testes.o
	gcc procedimento.o testes.o -o testes -std=c99 -Wall -lm
	
verifica: procedimento.o testes.o
	gcc -g -fsanitize=address procedimento.o testes.o -o testes -std=c99 -Wall -lm

procedimento.o: 
	gcc -c procedimento.c

testes.o:
	gcc -c testes.c

make run:
	./testes

clean:
	rm procedimento.o
	rm testes.o
	rm testes