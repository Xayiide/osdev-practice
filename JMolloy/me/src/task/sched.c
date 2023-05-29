#include <stdint.h>      /* uint_t */

#include "sched.h"
#include "task.h"
#include "lib/sys.h"     /* kmem_info_t */
#include "drivers/vga.h" /* printk */

static task_t  tasks[TASK_MAX_TASKS];
static task_t  ready[TASK_MAX_TASKS];
static uint8_t active_tasks;

void sched_init()
{
    uint8_t      i;
    char         name[TASK_NAME_LEN] = "UNUSEDX\0";
    //kmem_info_t *kmem;

    //kmem = sys_get_kmem_info();
    memset(&tasks, 0x00, sizeof(task_t) * TASK_MAX_TASKS);
    memset(&ready, 0x00, sizeof(task_t) * TASK_MAX_TASKS);

    for (i = 0; i < TASK_MAX_TASKS; i++)
    {
        tasks[i].stack_top = NULL;
        tasks[i].state     = UNUSED;
        tasks[i].prio      = 0;
        tasks[i].id        = i;
        name[6]            = i + 0x30; /* Cambia la X por el id en ASCII */
        strncpy(tasks[i].name, name, TASK_NAME_LEN);
    }
    active_tasks = 0;

}

void sched_diag()
{
    vga_color(VGA_BACK_BLACK, VGA_FORE_RED);
    printk(" === SCHED DIAGNOSIS ===\n");
    vga_color(VGA_BACK_BLACK, VGA_FORE_WHITE);
    printk("tasks: 0x%x\n",      &tasks);
    printk("ready: 0x%x\n",      &ready);
    printk("sched_init: 0x%x\n", sched_init);

}
