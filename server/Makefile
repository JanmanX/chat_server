CC=gcc
CFLAGS=-Wall -g -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LDFLAGS=
SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

all: $(OBJECTS)
	rm -r backup/*
	cp -r * backup
	$(CC) $(LDFLAGS) $(OBJECTS) -o /bin/server
	

clean:
	rm -v -f src/*.gch
	rm -v -f src/*.o
	
