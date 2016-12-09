all: euler_input
iptv_monitor: euler_input.c
	gcc -Wextra -pedantic -Wall$^ -o $@
clean:
	rm -f euler_input
