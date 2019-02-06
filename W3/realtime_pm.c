#include "realtime_pm.h"
#include <minix/com.h>
#include <minix/ipc.h>

/*************************************************
*		handle_vfs_message		 *
*************************************************/

struct rt_struct handle_vfs_message(message rt_msg)
{
	struct rt_struct output; 
	int* data;
	
	data = (int*)&rt_msg;
	/* Design of message: 
	int(endpoint)-int(type)-int(S)-(p)-(c)-(d)-(p)*/

	/* Find and extract the values after casting the message to an int[]*/
    	output.start_time = data[2];
	output.period = data[3];
	output.comp_time = data[4];
	output.deadline = data[5];
	output.rt_pid = data[6];

	/* Throw data back in the shape of a struct*/
	return output;        
}


