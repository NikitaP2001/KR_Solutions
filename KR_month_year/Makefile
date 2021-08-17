CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.c date.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=Date

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
