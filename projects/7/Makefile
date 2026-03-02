CFLAGS = -Wall -Wextra -Werror

grayscaler: grayscaler.o ppm.o
	$(CC) $(CFLAGS) -o $@ $^

grayscaler.o: grayscaler.c ppm.h
	$(CC) $(CFLAGS) -c grayscaler.c

ppm.o: ppm.c ppm.h
	$(CC) $(CFLAGS) -c ppm.c

clean:
	rm -f grayscaler *.o *.ppm