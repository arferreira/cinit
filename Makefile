build:
	gcc -o cinit main.c

install: build
	sudo cp cinit /usr/local/bin/

uninstall:
	rm -f /usr/local/bin/cinit
