CC = gcc
CFLAGS = -Wall -Werror

all: calc

calc: calc.o 
	$(CC) $(CFLAGS) calc.o -o calc
calc.o: calc.c
	$(CC) $(CFLAGS) -c -g calc.c
clean:
	rm -f *~
	rm -f calc
	rm -f *.o