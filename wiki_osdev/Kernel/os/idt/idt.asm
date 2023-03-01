section .asm

global enable_ints
global disable_ints

enable_ints:
    sti
    ret

disable_ints:
    cli
    ret


