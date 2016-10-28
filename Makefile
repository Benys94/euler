CC := gcc
CFLAGS := -std=c99 -Wall -Wextra -pedantic

dfs: dfs.o stack.o
	$(CC) $(CFLAGS) $^ -o $@

dfs.o: dfs.c
	$(CC) $(CFLAGS) -c $< -o $@

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o 2>/dev/null || true
	rm dfs 2>/dev/null || true

.PHONY: dfs clean
