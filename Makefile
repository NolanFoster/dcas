CC=gcc
CFLAGS=-I.
DEPS = drone_scheduler.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -w -lpthread -lrt

drone_scheduler: drone_scheduler.o drone_func.o
	$(CC) -o drone_scheduler drone_scheduler.o drone_func.o -I. -w -lpthread -lrt

clean:
	$(RM) count *.o *~
