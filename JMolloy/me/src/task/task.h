#ifndef _TASK_H_
#define _TASK_H_

#include <stdint.h>

typedef struct
{
    uint32_t eax, ebx, ecx, edx, esi, edi, esp, ebp, eip, eflags, cr3;
} Registers;

typedef struct
{
    Registers regs;
    struct Task *next;
} Task;

void initTasking(void);
void createTask(Task *, void(*)(), uint32_t);
void yield(void);

extern void switchTask(Registers *old, Registers *new); /* boot.asm */

#endif
