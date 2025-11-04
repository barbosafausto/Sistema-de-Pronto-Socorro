all: procedimento.o paciente.o registro.o testes.o
	gcc procedimento.o paciente.o registro.o testes.o -o testes -std=c99 -Wall -lm

verifica: procedimento.o paciente.o registro.o testes.o
	gcc -g -fsanitize=address procedimento.o historico.o testes.o -o testes -std=c99 -Wall -lm

procedimento.o: 
	gcc -c ../TAD_Procedimento/procedimento.c 

paciente.o: 
	gcc -c ../TAD_Paciente/paciente.c 

registro.o:
	gcc -c registro.c

testes.o:
	gcc -c testes.c
	
make run:
	./testes

clean:
	rm *.o
	rm testes