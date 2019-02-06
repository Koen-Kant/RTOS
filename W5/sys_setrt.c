#include "syslib.h"

PUBLIC int sys_setrt(s_time, c_time, per, dl, is_rt)
	int s_time;
	int c_time;
	int per;	
	int dl;
	int is_rt;
{
	/* hand of the inforamtion to the kernal call */
	message m;
	*((int*)&m+2) = s_time;
	*((int*)&m+3) = c_time;
	*((int*)&m+4) = per;
	*((int*)&m+5) = dl;
	*((int*)&m+5) = is_rt;

	return _kernel_call(SYS_SETRT, &m);
}
