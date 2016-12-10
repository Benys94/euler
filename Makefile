#File: Makefile
#Description: Makefile for main program.
#Author: Jan Morávek <xmorav33@stud.fit.vutbr.cz>
CC = gcc
CFLAGS = -pedantic -Wall -Wextra -std=c99
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
PROGRAMS = euler

all: euler

euler: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm *.o $(PROGRAMS) 2>/dev/null || true
