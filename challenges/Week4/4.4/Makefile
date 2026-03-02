CC=gcc
CCOPTS=-Wall -Wextra
LIBS=

SRCS=$(wildcard *.c)
TARGETS=$(SRCS:.c=)

.PHONY: all clean

all: $(TARGETS)

clean:
	rm -f $(TARGETS) fifa

%: %.c
	$(CC) $(CCOPTS) -o $@ $< $(LIBS)
    
