CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic 

all: banhammer

banhammer: banhammer.o speck.o parser.o node.o ht.o bf.o ll.o bv.o
	$(CC) $(CFLAGS) -o banhammer banhammer.o speck.o parser.o node.o ht.o bf.o ll.o bv.o

banhammer.o: banhammer.c
	$(CC) $(CFLAGS) -c banhammer.c

speck.o: speck.c
	$(CC) $(CFLAGS) -c speck.c

parser.o: parser.c
	$(CC) $(CFLAGS) -c parser.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

ht.o: ht.c
	$(CC) $(CFLAGS) -c ht.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

bf.o: bf.c
	$(CC) $(CFLAGS) -c bf.c 

ll.o: ll.c
	$(CC) $(CFLAGS) -c ll.c

format:
	clang-format -i -style=file *.c *.h

clean:
	rm -f banhammer *.o

scan-build: clean
	scan-build make
