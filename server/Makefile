CC=gcc
CFLAGS=-Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LDFLAGS=-pthread
SOURCES=$(wildcard src/**/*.c src/*.c src/**/*.h src/*.h)
OBJECTS=$(wildcard src/**/*.o src/*.o,$(SOURCES))

all: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o bin/server
	

clean:
	rm -v -f src/*.gch
	rm -v -f src/*.o
	rm -v -f bin/*	
