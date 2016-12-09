CC = gcc
CFLAGS = -pedantic -Wall -Wextra
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
PROGRAMS = euler

all: euler

euler: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm *.o $(PROGRAMS)
