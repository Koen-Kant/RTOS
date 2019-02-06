#include "../realtime_kernel.h"
#include "kernel/system.h"
#include <unistd.h>

#if USE_WFNP
int do_wfnp(void)
{
	sleep(1);
	
	return 0;
}
#endif
