CC=gcc
CFLAGS=-g -Wall -fPIC -I.
PLIKI=sync
LIBS=-pthread
RES=libsync.so

all: $(RES)
	
$(RES): $(PLIKI:=.o)
	$(CC) -shared $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ $(LIBS)

clean:
	rm -f $(PLIKI:=.o)

.PHONY: all clean
