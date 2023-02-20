#ifndef _CONFIG_H_
#define _CONFIG_H_

#define CHAMACOS_TOTAL_INTERRUPTS 512
#define KERNEL_CODE_SELECTOR      0x08
#define KERNEL_DATA_SELECTOR      0x10

#define CHAMACOS_HEAP_SIZE_BYTES 1024*1024*100 /* 100 MB */
#define CHAMACOS_HEAP_BLOCK_SIZE 4096

/* el heap empezará en 0x1000000 */
#define CHAMACOS_HEAP_ADDR       0x01000000 /* osdev memory map x86 */
/* la tabla del heap en 0x00007FFF */
#define CHAMACOS_HEAP_TABLE_ADDR 0x00007FFF

#endif
