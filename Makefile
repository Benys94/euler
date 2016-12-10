CC = gcc
CFLAGS = -pedantic -Wall -Wextra -std=c99
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
PROGRAMS = euler

all: euler

euler: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	gcc $(CFLAGS) -c $^ -o $@

clean:
	rm *.o $(PROGRAMS) 2>/dev/null || true
