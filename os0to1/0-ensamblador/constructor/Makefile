CC = gcc
CFLAGS = -g

SRCS = constructor1 constructor2 constructor3 destructor1 preinit1

all: $(SRCS)

constructor1: constructor1.c
	$(CC) $(CFLAGS) $^ -o $@

constructor2: constructor2.c
	$(CC) $(CFLAGS) $^ -o $@

constructor3: constructor3.c
	$(CC) -m32 $(CFLAGS) $^ -o $@

destructor1: destructor1.c
	$(CC) $(CFLAGS) $^ -o $@

preinit1: preinit1.c
	$(CC) -m32 $(CFLAGS) $^ -o $@

clean:
	rm -f $(SRCS)

re: clean all
