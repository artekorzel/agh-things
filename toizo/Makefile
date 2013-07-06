CC=gcc
CFLAGS=-Wall
PLIKI=toizo

all: $(PLIKI) run

%: %.c
	$(CC) $(CFLAGS) -o $@ $^

run: $(PLIKI)
	./$^ test

clean:
	rm -f toizo

.PHONY: all run clean 
