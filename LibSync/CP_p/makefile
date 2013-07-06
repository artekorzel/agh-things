CC=gcc
CFLAGS=-Wall -I../lib/ -L../lib/ -Wl,-rpath ../lib/
VPATH=./src/
PLIKI=CP_p
LIBS=-lsync

all: $(PLIKI)

%: %.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean_logs:
	rm -f log/* log.log

clean:
	rm -f $(PLIKI)

.PHONY: all clean
