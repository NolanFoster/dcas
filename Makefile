CC=gcc
CFLAGS=-I.
DEPS = dcas.c
LDFLAGS=-lncurses

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -w -lpthread -lrt -lncurses

dcas: dcas.o drone_func.o dcas_func.o map.o
	$(CC) -o dcas dcas.o drone_func.o dcas_func.o map.o -I. -w -lpthread -lrt -lncurses

clean:
	$(RM) count *.o *~
