all: procedimento.o historico.o paciente.o testes.o
	gcc paciente.o procedimento.o historico.o testes.o -o testes -std=c99 -Wall -lm

verifica: procedimento.o historico.o paciente.o testes.o
	gcc -g -fsanitize=address paciente.o procedimento.o historico.o testes.o -o testes -std=c99 -Wall -lm

paciente.o:
	gcc -c ../TAD_Paciente/paciente.c 

procedimento.o: 
	gcc -c ../TAD_Procedimento/procedimento.c 

historico.o:
	gcc -c historico.c

testes.o:
	gcc -c testes.c

make run:
	./testes

clean:
	rm *.o
	rm testes