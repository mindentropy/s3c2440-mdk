CC=gcc
CFLAGS= -g -Wall

all: uploader

uploader: uploader.o
	$(CC) $(CFLAGS) $^ -o $@

uploader.o: uploader.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -rfv uploader *.o *.gch
