CC = gcc
CFLAGS = -Wall -Wextra

add-nbo: add-nbo.c
	$(CC) $(CFLAGS) -o add-nbo add-nbo.c

clean:
	rm -f add-nbo

