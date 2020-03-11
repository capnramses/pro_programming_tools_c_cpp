CC=gcc
INCLUDES=two.h

all: main.o two.o
	$(CC) main.o two.o -lm

.PHONY : clean
clean:
	rm -f *.o a.out

%.o: %.c $(INCLUDES)
	$(CC) -c -o $@ $<
