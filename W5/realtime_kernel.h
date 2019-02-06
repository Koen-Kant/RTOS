#ifndef _REALTIME_K_H_
#define _REALTIME_K_H_

typedef struct rt_k_struct {
    /*make the rt_data struct avaiable in kernel */
    int start_time;
    int comp_time;
    int period;
    int deadline;
    int is_rt;
    int wfnp;
};

#endif /* _REALTIME_K_H_ */
