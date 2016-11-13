CC := gcc
CFLAGS := -std=c99 -Wall -Wextra -pedantic

dfs: dfs.o stack.o pool.o error.o
	$(CC) $(CFLAGS) $^ -o $@

dummy: dummy.o pool.o error.o
	$(CC) $(CFLAGS) $^ -o $@

dfs.o: dfs.c
	$(CC) $(CFLAGS) -c $< -o $@

dummy.o: dummy.c
	$(CC) $(CFLAGS) -c $< -o $@

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c $< -o $@

error.o: error.c error.h
	$(CC) $(CFLAGS) -c $< -o $@

pool.o: pool.c pool.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o 2>/dev/null || true
	rm dfs 2>/dev/null || true
	rm dummy 2>/dev/null || true

.PHONY: all dfs clean dummy
