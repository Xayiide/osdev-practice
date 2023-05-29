#ifndef _SCHED_H_
#define _SCHED_H_

#include <stdint.h> /* uint_t */
#include "task.h"


void    sched_init(void);
void    sched_diag(void);
void   *sched_get_tasks_array(void);
task_t *sched_get_task(uint8_t tid);

#endif
