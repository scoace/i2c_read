CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=i2c_read.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=i2c_read

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -O -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -rf *.o $(EXECUTABLE)
