AS      = nasm
AFLAGS = -f bin

SRC = prueba1.asm
TGT = $(SRC:.asm=.out)

all:  $(TGT)

elf: $(SRC)
	$(AS) -f elf $^ -o $(TGT:.out=.elf)

$(TGT): $(SRC)
	$(AS) $(AFLAGS) $^ -o $@

clean:
	@rm -f $(TGT)

re: clean all
