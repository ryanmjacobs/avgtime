CC=gcc
CFLAGS=-c -Wall -O3
LDFLAGS=
SOURCES=src/args.c src/main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=avgtime
MAN=avgtime.1

all: $(SOURCES) $(EXECUTABLE) man
            
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -vf $(EXECUTABLE)
	@rm -vf ${MAN}.gz
	@find -type f -iname '*.o' -exec rm -vf {} \;

man:
	gzip -kf -9 ${MAN}

install:
	install -Dm 775 ${EXECUTABLE} /usr/bin/${EXECUTABLE}
	install -Dm 644 ${MAN} /usr/share/man/man1/${MAN}

uninstall:
	@rm -vf /usr/bin/${EXECUTABLE}
	@rm -vf /usr/share/man/man1/${MAN}
