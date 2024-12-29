all:
	gcc src/scrjolly.c $(shell pkgconf --cflags --libs ncursesw) -o bin/scrjolly

clean:
	rm bin/scrjolly

install:
	cp bin/scrjolly /usr/local/bin/scrjolly
