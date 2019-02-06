#include "../realtime_kernel.h"
#include "kernel/system.h"
#include <unistd.h>

#if USE_WFNP
int do_wfnp(void)
{
	/*
	Suspend the system until the period manaer wakes it.
	*/
	pause();	

	return 0;
}
#endif
