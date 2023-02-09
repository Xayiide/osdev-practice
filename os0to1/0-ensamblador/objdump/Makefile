CC = gcc
CFLAGS = -g

SRC = hola.c
TGT = $(SRC:.c=)

all: $(TGT) constructor

$(TGT): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

constructor: constructor.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	@rm -f $(TGT) constructor

re: clean all
