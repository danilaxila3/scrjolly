all:
	gcc src/scrjolly.c $(shell pkgconf --cflags --libs ncursesw) -o bin/scrjolly
