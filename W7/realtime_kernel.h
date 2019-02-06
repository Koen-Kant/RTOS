#ifndef _REALTIME_K_H_
#define _REALTIME_K_H_

#include "proc.h"

typedef struct rt_k_struct {
    int start_time;
    int comp_time;
    int period;
    int deadline;
    int is_rt;
    int wfnp;
    endpoint_t p_endp; 
};

void add_proc_to_rt_que();
int remove_proc_from_rt_que(struct proc *rt_process);
proc* find_proc_with_pid(int pid);
void execute_first_rt_proc_from_que();
Void manage_que();

#endif /* _REALTIME_K_H_ */
