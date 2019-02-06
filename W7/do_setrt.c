#include "../realtime_kernel.h"
#include "kernel/system.h"

#if USE_SETRT
int do_setrt(struct rt_k_struct rt_data)
{
	proc rt_process;
	rt_process = proc_addr(rt_data.p_endp);	

	rt_process->rt_kdata.start_time = rt_data.start_time;
	rt_process->rt_kdata.comp_time = rt_data.comp_time;
	rt_process->rt_kdata.period = rt_data.period;
	rt_process->rt_kdata.deadline = rt_data.deadline;
	rt_process->rt_kdata.is_rt = rt_data.is_rt;
	rt_process->rt_kdata.wfnp = 0;

	add_proc_to_rt_que();	
	return 0;
}
#endif
