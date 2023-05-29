#include <stdint.h>
#include "task.h"

#include "mm/pmm.h"
#include "drivers/vga.h"

static Task *runningTask;
static Task mainTask;
static Task otherTask;

static void otherMain()
{
    printk("Multitasking world\n");
    yield();
}

void initTasking()
{
    asm volatile("movl %%cr3, %%eax; movl %%eax, %0;":"=m"(mainTask.regs.cr3)::"%eax");
    asm volatile("pushfl; movl (%%esp), %%eax; movl %%eax, %0; popfl;":"=m"(mainTask.regs.eflags)::"%eax");

    createTask(&otherTask, otherMain, mainTask.regs.eflags);
    mainTask.next = (struct Task *) &otherTask;
    otherTask.next = (struct Task *) &mainTask;

    runningTask = &mainTask;
}

void createTask(Task *task, void (*main)(), uint32_t flags)
{
    task->regs.eax    = 0;
    task->regs.ebx    = 0;
    task->regs.ecx    = 0;
    task->regs.edx    = 0;
    task->regs.esi    = 0;
    task->regs.edi    = 0;
    task->regs.eflags = flags;
    task->regs.eip    = (uint32_t) main;
    task->regs.esp    = (uint32_t) pmm_alloc_frame() /*+ 0x1000*/;
    task->next        = 0;
}

void yield()
{
    Task *last = runningTask;
    runningTask = (Task *) runningTask->next;
    switchTask(&last->regs, &runningTask->regs);
}
