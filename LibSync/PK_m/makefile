CC=gcc
CFLAGS=-Wall -g -I../lib/ -L../lib/ -Wl,-rpath ../lib/
VPATH=./src/
PLIKI=PK_m_a PK_m_b PK_m_c
LIBS=-lsync

all: $(PLIKI)

%: %.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean_logs:
	rm -f log/* log.log

clean:
	rm -f $(PLIKI)

.PHONY: all clean
