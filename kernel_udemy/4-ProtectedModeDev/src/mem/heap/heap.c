#include <stdbool.h> /* bool */
#include "status.h"
#include "mem/mem.h"
#include "kernel.h"
#include "heap.h"

static int heap_validate_table(void *ptr, void *end, struct heap_table *table) {
    int    res = 0;
    size_t table_size;
    size_t total_blocks;

    table_size   = (size_t) (end - ptr);
    total_blocks = table_size / CHAMACOS_HEAP_BLOCK_SIZE;

    if (table->total != total_blocks) {
        res = -EINVARG;
        goto out;
    }

out:
    return res;
}

static bool heap_validate_align(void *ptr) {
    return ((unsigned int)ptr % CHAMACOS_HEAP_BLOCK_SIZE == 0);
}

int heap_create(struct heap *heap, void *ptr, void *end,
                struct heap_table *table) {
    int    res = 0;
    size_t table_size = 0;

    if (!heap_validate_align(ptr) || !heap_validate_align(end)) {
        res = -EINVARG;
        goto out;
    }

    memset(heap, 0, sizeof(struct heap));
    heap->saddr = ptr;
    heap->table = table;

    res = heap_validate_table(ptr, end, table);

    if (res < 0) {
        goto out;
    }

    /* initialize every block in the heap table to 0 */
    table_size = sizeof(HEAP_BLOCK_TABLE_ENTRY) * table->total;
    memset(table->entries, HEAP_BLOCK_TABLE_ENTRY_FREE, table_size);
    

out:
    return res;   
}


static uint32_t heap_align_value_to_upper(uint32_t val) {
    if (val % CHAMACOS_HEAP_BLOCK_SIZE == 0) {
        return val; /* already aligned */
    }

    val = (val - (val % CHAMACOS_HEAP_BLOCK_SIZE));
    val += CHAMACOS_HEAP_BLOCK_SIZE;

    return val;
}

static int heap_get_entry_type(HEAP_BLOCK_TABLE_ENTRY entry) {
    return entry & 0x0F; /* 00001111 */
}


int heap_get_start_block(struct heap *heap, int total_blocks) {
    struct heap_table *table;
    size_t i;
    int bc = 0;  /* block count */
    int bs = -1; /* block start */

    table = heap->table;

    for (i = 0; i < table->total; i++) {
        if (heap_get_entry_type(table->entries[i]) != HEAP_BLOCK_TABLE_ENTRY_FREE) {
            bc = 0;
            bs = -1;
            continue;
        }

        /* if this is the first block */
        if (bs == -1) {
            bs = i;
        }

        bc++;
        if (bc == total_blocks) {
            /* found the needed size of blocks */
            break;
        }
    }

    if (bs == -1) {
        return -ENOMEM;
    }
    return bs;

}

void *heap_block_to_address(struct heap *heap, int block) {
    return heap->saddr + (block * CHAMACOS_HEAP_BLOCK_SIZE);
}

void heap_mark_blocks_taken(struct heap *heap, int start_block, int total_blocks) {
    int end_block, i;

    end_block = (start_block + total_blocks) - 1;

    HEAP_BLOCK_TABLE_ENTRY entry = HEAP_BLOCK_TABLE_ENTRY_TAKEN | HEAP_BLOCK_IS_FIRST;

    if (total_blocks > 1) {
        entry |= HEAP_BLOCK_HAS_NEXT;
    }

    for (i = start_block; i <= end_block; i++) {
        heap->table->entries[i] = entry;
        entry = HEAP_BLOCK_TABLE_ENTRY_TAKEN;
        if (i != end_block - 1) {
            entry |= HEAP_BLOCK_HAS_NEXT;
        }
    }
}


void *heap_malloc_blocks(struct heap *heap, uint32_t total_blocks) {
    void *address = 0;
    int start_block;

    start_block = heap_get_start_block(heap, total_blocks);
    if (start_block < 0) {
        goto out;
    }

    address = heap_block_to_address(heap, start_block);

    /* mark the block as taken */
    heap_mark_blocks_taken(heap, start_block, total_blocks);
out:
    return address;

}

int heap_address_to_block(struct heap *heap, void *address) {
    return ((int) (address - heap->saddr)) / CHAMACOS_HEAP_BLOCK_SIZE;
}

void heap_mark_blocks_free(struct heap *heap, int starting_block) {
    int i;
    struct heap_table *table;

    table = heap->table;

    for (i = starting_block; i < (int)table->total; i++) {
        HEAP_BLOCK_TABLE_ENTRY entry = table->entries[i];
        table->entries[i] = HEAP_BLOCK_TABLE_ENTRY_FREE;

        if (!(entry & HEAP_BLOCK_HAS_NEXT)) {
            break; /* reached end of allocation */
        }
    }
}

void *heap_malloc(struct heap *heap, size_t size) {
    size_t aligned_size;
    uint32_t total_blocks;

    aligned_size = heap_align_value_to_upper(size);
    total_blocks = aligned_size / CHAMACOS_HEAP_BLOCK_SIZE;

    return heap_malloc_blocks(heap, total_blocks);
}

void heap_free(struct heap *heap, void *ptr) {
    heap_mark_blocks_free(heap, heap_address_to_block(heap, ptr));
}
