TARGETS=reader

.PHONY: all clean

all: $(TARGETS)

reader: reader.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS) *.txt