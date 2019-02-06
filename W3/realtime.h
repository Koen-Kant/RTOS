#ifndef _REALTIME_H_
#define _REALTIME_H_

typedef struct rt_struct {
    int start_time;
    int comp_time;
    int period;
    int deadline;
    int rt_pid;
};

void my_rt_function(char *m_stack, int m_f_len, int proc_id);

#endif /* _REALTIME_H_ */
