#include "syslib.h"

PUBLIC int sys_wfnp(void)
{
	message m;

	return _kernel_call(SYS_WFNP, &m);
}
