CC=gcc
CFLAGS=-c -Wall -O3
LDFLAGS=
SOURCES=src/args.c src/main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=avgtime

all: $(SOURCES) $(EXECUTABLE)
            
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -vf $(EXECUTABLE)
	@find -type f -iname '*.o' -exec rm -vf {} \;
