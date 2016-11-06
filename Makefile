# Project: Euler-generator
# Author:  Marek Jankech <xjanke01@stud.fit.vutbr.cz>

CC := gcc 
CFLAGS := -std=c99 -Wall -Wextra -pedantic 

generator: main.o generator.o 
	$(CC) $(CFLAGS) $> -o $@ 

main.o: main.c 
	$(CC) $(CFLAGS) -c $< -o $@ 

generator.o: generator.c generator.h 
	$(CC) $(CFLAGS) -c $< -o $@ 

clean: 
	rm -f *.o 2>/dev/null || true 
	rm generator 2>/dev/null || true 

.PHONY: generator clean
