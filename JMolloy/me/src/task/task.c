#include <stdint.h>
#include "task.h"

#include "mm/pmm.h"
#include "drivers/vga.h"

static Task *runningTask;
static Task mainTask;
static Task otherTask;

static void task_diag(Task *t);

static void otherMain()
{
    printk("Multitasking world\n");
    yield();
}

void initTasking()
{
    asm volatile("pushfl; movl (%%esp), %%eax; movl %%eax, %0; popfl;":"=m"(mainTask.regs.eflags)::"%eax");

    createTask(&otherTask, otherMain, mainTask.regs.eflags);
    mainTask.next = (struct Task *) &otherTask;
    otherTask.next = (struct Task *) &mainTask;

    runningTask = &mainTask;
}

void createTask(Task *task, void (*main)(), uint32_t flags)
{
    task->regs.edi    = 0x00000ED1;
    task->regs.esi    = 0x00000E51;
    /* Aquí iría EBP */
    task->regs.esp    = (uint32_t) pmm_alloc_frame() /*+ 0x1000*/;
    task->regs.ebx    = 0x00000EBB;
    task->regs.edx    = 0x00000EDD;
    task->regs.ecx    = 0x00000ECC;
    task->regs.eax    = 0x00000EAA;
    task->regs.eflags = flags;
    task->regs.eip    = (uint32_t) main;
    task->next        = 0;
}

void yield()
{
    Task *last = runningTask;
    runningTask = (Task *) runningTask->next;
    task_diag(last);
    switchTask(&last->regs, &runningTask->regs);
}

static void task_diag(Task *t)
{
    printk("Task @ %x\n", t);
    printk("Regs @ %x\n", &t->regs);
    printk("[EDI @ %x]   0x%x\n", &t->regs.edi,    t->regs.edi);
    printk("[ESI @ %x]   0x%x\n", &t->regs.esi,    t->regs.esi);
    printk("[EBP @ %x]   0x%x\n", &t->regs.ebp,    t->regs.ebp);
    printk("[ESP @ %x]   0x%x\n", &t->regs.esp,    t->regs.esp);
    printk("[EBX @ %x]   0x%x\n", &t->regs.ebx,    t->regs.ebx);
    printk("[EDX @ %x]   0x%x\n", &t->regs.edx,    t->regs.edx);
    printk("[ECX @ %x]   0x%x\n", &t->regs.ecx,    t->regs.ecx);
    printk("[EAX @ %x]   0x%x\n", &t->regs.eax,    t->regs.eax);
    printk("[EFL @ %x]   0x%x\n", &t->regs.eflags, t->regs.eflags);
    printk("[EIP @ %x]   0x%x\n", &t->regs.eip,    t->regs.eip);
    printk("Next @ %x -> 0x%x\n", &t->next, t->next);
}
