#ifndef _REALTIME_H_
#define _REALTIME_H_

typedef struct mproc {
    int start_time;
    int comp_time;
    int period;
    int deadline;
};

#endif /* _REALTIME_H_ */

