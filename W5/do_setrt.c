#include "../realtime_kernel.h"
#include "kernel/system.h"
#include <lib/libsys/kprintf.c>

#if USE_SETRT
int do_setrt(struct rt_k_struct rt_data)
{
	/* take the process item from the kernel and 
	fill in the rt_data information */
	rp->rt_kdata.start_time = rt_data.start_time;
	rp->rt_kdata.comp_time = rt_data.comp_time;
	rp->rt_kdata.period = rt_data.period;
	rp->rt_kdata.deadline = rt_data.deadline;
	rp->rt_kdata.is_rt = rt_data.is_rt;
	rp->rt_kdata.wfnp = 0;	

	printf("do_setrt\n");
	return 0;
}
#endif
