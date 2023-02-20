#include "kheap.h"
#include "heap.h"
#include "config.h"
#include "kernel.h"

struct heap       kernel_heap;
struct heap_table kernel_heap_table;

/* Size of heap: 100 MB = 1024 * 1024 * 100
 * This gives us 25600 chunks of 4096 bytes each (heap entries) */

void kheap_init() {
    void *end;
    int total_table_entries;
    int res;

    total_table_entries = CHAMACOS_HEAP_SIZE_BYTES/CHAMACOS_HEAP_BLOCK_SIZE;   

    kernel_heap_table.entries = (HEAP_BLOCK_TABLE_ENTRY *) CHAMACOS_HEAP_TABLE_ADDR;
    kernel_heap_table.total   = total_table_entries;

    end =  (void *) (CHAMACOS_HEAP_ADDR + CHAMACOS_HEAP_SIZE_BYTES);

    res = heap_create(&kernel_heap, (void *)(CHAMACOS_HEAP_ADDR), end, &kernel_heap_table);

    if (res < 0) {
        print("Failed to create heap\n");
    }
}

void *kmalloc(size_t size) {
    return heap_malloc(&kernel_heap, size);
}

void kfree(void *ptr) {
    heap_free(&kernel_heap, ptr);
}
