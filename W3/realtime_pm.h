#include <minix/ipc.h>

#ifndef _REALTIME_PM
#define _REALTIME_PM

typedef struct rt_struct {
    int start_time;
    int comp_time;
    int period;
    int deadline;
    int rt_pid;
};

struct rt_struct handle_vfs_message(message rt_msg);

#endif /*_REALTIME_PM */
