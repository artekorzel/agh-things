CC=gcc
CFLAGS=-g -Wall -I../lib/ -L../lib/ -Wl,-rpath ../lib/
VPATH=./src/
PLIKI=PK_p_a PK_p_b PK_p_c
LIBS=-lsync

all: $(PLIKI)

%: %.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean_logs:
	rm -f log/* log.log

clean:
	rm -f $(PLIKI)

.PHONY: all clean
