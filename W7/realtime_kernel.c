#include "realtime_kernel.h"
#include "proc.h"

void add_proc_to_rt_que()
{
	proc *rtp, current, previous;
	int i=0, done=0, found=0; cycles=0;

        /*get the rt-process from the rdy_list. by looping trough all the schedueling list*/
	for(i=0;i<NR_SCHED_QUEUES;i++)
		current = rdy_head[i]; /*set the start on the begining of the list*/
		while (!done)
		{
			if(current->rt_data.is_rt) /*check if the entry is rt and if so, remember and remove*/
			{	
				rtp=current;
				if(cycles)/*if we're on entry 2 or higher use the previous entry we remembered */
				{previous.p_nextready = current.p_nextready;}
				else
				{rdy_head[i] = current.p_nextready;} /*else use the head of the list */
				done = 1;				
				found = 1;
			}
	
			if(!current.p_nextready) /* continue if there is a next extry */
			{
				previous = current;
				current = current.p_nextready;
				cycles++;
			}
			else /*or end with this list and on with the the next 8/
			{
				done =1;
			}
				
		} /*end While and reset the values*/
		done = 0;
		cycles=0;
	}/*end for, we looped trough the lists*/
		
	if(found) /* when found */
	{
        	if (!rt_que_head) /* add it to the rt_que as defined in proc.h */
        	{                                   
        	        rt_que_head = rt_que_tail = rtp;	/* create a new queue */
        	        rtp->q_nextready = NULL;           	/* mark new end */
        	}
        	else 
        	{                                        	/* add to tail of queue */
        	        rt_que_tail->p_nextready = rtp;   	/* chain tail of queue */
        	        rt_que_tail = rtp;                	/* set new queue tail */
        	        rtp->p_nextready = NULL;          	/* mark new end */
        	}
	}


}

int remove_proc_from_rt_que(struct proc *rt_process)
{	
        proc current, previous;
        int i=0, done=0,found=0, cycles=0;

       	current = rt_que_head;
        while (!done) /* start at the rt_head and loop trouh it until 
	you find the matching process (or reach the end) and return 1 
	if successful and 0 if failed */ 
        {
                if(current == rt_process)
                {
			if(cycles)
                        {previous.p_nextready = current.p_nextready;}
                        else
                        {rdy_head[i] = current.p_nextready;}
                        done = 1;
                        found = 1;
               	}
		if(!current.p_nextready)
                {
                	previous = current;
                        current = current.p_nextready;
                        cycles++;
              	}
             	else
            	{
                 	done = 1;
            	}
	}
	return found;		
	
}

void execute_first_rt_proc_from_que()
{
	/* move the first entry from the rt que to the top of the 
	   highest priority que. */
	proc *tmp;
	tmp = rdy_head[0];
	rdy_head[0] = rt_que_head;
	rdy_head[0].P_nextready = tmp;
	return;
}

Void manage_que()
{
	int i, done;
	proc *entry1, *entry2, *previous;
	/* this function makes use of the bubble sort algortihm to order 
	the list of processes so the lowest deadline sits at the head. */

	/* if there is one entery, the list is sorted */
	if(!rt_que_head.p_nextready){return;}
	
	done = 0;
	
	entry1 = rt_que_head;
	entry2 = rt_yue_head.p_nextready;
	
	/* go trough the list stariting with the head and the first entry */
        if(entry1->rt_k_data.deadline > entry2->rt_k_data.deadline)
        {
		rt_que_head=entry2;
		rt_que_head.p_nextready = entry1;
        }
                previous = rt_qeu_head;


	while(!done)
	{	/* when we found the end of the list start over again */
		if(!entry2.p_nextready)
		{entry1 = rt_que_head; entry2=rt_que_head.p_nextready;}
		entry1 = entry2;
		entry2 = entry2.p_nextready;
		if(entry1->rt_k_data.deadline > entry2->rt_k_data.deadline)
		{
			entry2.p_nextready = entry1;
			previous.p_nextready = entry2;
		}
		/* if the list is ordered we can stop
		done = check_ordered_rt_que();
	}
}

check_ordered_rt_que()
{
	int previous;
	proc *current;
	current = rt_que_head.p_nextready;
	/* prepare the data needed for the comparison */
	previous = rt_que_head->rt_k_data.deadline;
	/* and keep oing until you find the end on the line
	while(current.p_nextready)
	{
		if(previous>current->rt_k_data.deadline)
			{ /* if there is any instance where the previous 
		  	     value was higher the list isn't ordered */
				return 0;
			}
		/* prepare for the next run */
		previous = current->rt_k_data.deadline;
		current = current.p_nextready;
	}
	/*the list is ordered */
	return 1;
}
