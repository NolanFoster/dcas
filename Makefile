CC=gcc
CFLAGS=-I.
DEPS = dcas.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -w -lpthread -lrt

dcas: dcas.o drone_func.o dcas_func.o
	$(CC) -o dcas dcas.o drone_func.o dcas_func.o -I. -w -lpthread -lrt

clean:
	$(RM) count *.o *~
