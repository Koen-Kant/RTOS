#include "realtime.h"

/*===========================================================================*
 *				my_rt_function				     *
 *===========================================================================*/

void my_rt_function(char *m_stack, int m_f_len, int proc_id)
{
    /* the declaration of the values, two indexes, an indicator if we
    found "-Realtime", an int to hold the argc and a counter for the 
    number of rt-related arguments we've found */

    int i, j, is_realtime, argc, found_rt_args;
    struct rt_struct out, found;
    int *baseint, *stackint;

    /* two int* to the stack, baseint remains what it is as stackint will
    be incremented */    
    baseint = (int*)m_stack;
    stackint = (int*)m_stack;

    /* two int* to the stack, baseint remains what it is as stackint will
    be incremented */
    out.comp_time = 1;
    out.start_time = 0;
    out.period = 5;
    out.deadline = 5;
    out.rt_pid = proc_id;

    /* these 4 ints in a struct hold an inital -1 value(unset) and will 
    recieve the value the usr gives(if any)*/
    found.comp_time = -1;
    found.start_time = -1;
    found.period = -1;
    found.deadline = -1;

    /* init is_realtime and found rt_args*/
    is_realtime = 0;
    found_rt_args = 0;

    /* Starting at the second entry in the stack argc[0],  we retrieve
    a character pointer that is used to check if its string matches
    -Realtime, ENV, -S=, -p=, -c= and -d=, and if so, retrieve the
    value, remove the pointer from the stack and fix the remaining argv
    pointers*/

    /*begin at the beginning, and keep going until all the data in
    the argvs is checked, so until we checked*/

    /* start cheking at argv[0] and check if it matcher any of the RT 
    values*/
    argc = stackint[0];
    stackint++;
    for(i=0;i<argc;i++)
    {
        if(strncmp("-Realtime", m_stack + (*stackint),9)==0)
        {
	    /* if it matches, take action special to the arg */	
            is_realtime = 1;

	    /* if it matches, take action special to the arg */
            memcpy((char*)stackint, ((char*)stackint)+sizeof(int*), m_f_len-(2+i)*4);
            
	    /* and check and re-adjust the other argumetns so that they 
	    point back at their value, minus 4 because the stack was move 4 bytes 
	    left*/
	    for(j=1;j<argc;j++)
            {
                baseint[j]=baseint[j]-4;
            }
	    /*as we remove an argument, subtrackt argc */
	    argc--;
	    /*as we didn't move t the next argument, because it came to 
	    us we shouldn't check the next value*/
	    i--;
	    /*and keep track of the found data*/
            found_rt_args++;
        }
        /*check if the var is -S and extract the value*/
        else if(strncmp("-S=", m_stack + (*stackint),3)==0)
        {
            found.start_time=strtoul((char *)(m_stack+(*stackint)+3),0,10);

            memcpy((char*)stackint, ((char*)stackint)+sizeof(int*), m_f_len-(2+i)*4);
            for(j=1;j<argc;j++)
            {
                baseint[j]=baseint[j]-4;
            }
	    argc--;
	    i--;
            found_rt_args++;
        }
        /*same for -c*/
        else if(strncmp("-c=", m_stack + (*stackint),3)==0)
        {
            found.comp_time=strtoul((char *)(m_stack+(*stackint)+3),0,10);

            memcpy((char*)stackint, ((char*)stackint)+sizeof(int*), m_f_len-(2+i)*4);
            for(j=1;j<argc;j++)
            {
                baseint[j]=baseint[j]-4;
            }
	    argc--;
	    i--;
            found_rt_args++;
        }
        /*and -p*/
        else if(strncmp("-p=", m_stack + (*stackint),3)==0)
        {
            found.period=strtoul((char *)(m_stack+(*stackint)+3),0,10);

            memcpy((char*)stackint, ((char*)stackint)+sizeof(int*), m_f_len-(2+i)*4);
            for(j=1;j<argc;j++)
            {
                baseint[j]=baseint[j]-4;
            }
	    argc--;
	    i--;
        found_rt_args++;
        }
        /*and -d*/
        else if(strncmp("-d=", m_stack + (*stackint),3)==0)
        {
            found.deadline=strtoul((char *)(m_stack+(*stackint)+3),0,10);

            memcpy((char*)stackint, ((char*)stackint)+sizeof(int*), m_f_len-(2+i)*4);
            for(j=1;j<argc;j++)
            {
                baseint[j]=baseint[j]-4;
            }
	    argc--;
	    i--;
            found_rt_args++;
        }
        else
        {
            stackint++;
        }
    }

    /*alter the argc value on the stack to reflect the new status*/
    baseint[0]=baseint[0]-found_rt_args;

    /*check if the var is the ENV var and override the default data*/
    /*jump over the separating zero*/
    stackint++;
    while((*stackint)!=0)
    {
        /* check all the enviroment values until we find the second 0
        and fix them by subtrackting 4*the number of rt_args found */
	*stackint = (*stackint)-found_rt_args*4;
        if(strncmp("REALTIME=c=",m_stack+(*stackint),11)==0)
        {
            out.comp_time=strtoul((char *)(m_stack+(*stackint)+11),0,10);
            out.start_time=strtoul((char *)(m_stack+(*stackint)+15),0,10);
            out.period=strtoul((char *)(m_stack+(*stackint)+19),0,10);
            out.deadline=strtoul((char *)(m_stack+(*stackint)+23),0,10);
        }
        stackint++;
    }

    /* after cheking the stack, if the is_realtime var was set we shall
    print the data*/

    if(is_realtime==1)
    {
    /* if this S,c,p and/or d var was defined by the user then we
    over-ride the data contained in "base_(var)"*/
        if(found.start_time!=-1)
        {
            out.start_time=found.start_time;
        }
        if(found.comp_time!=-1)
        {
            out.comp_time=found.comp_time;
        }
        if(found.period!=-1)
        {
            out.period=found.period;
        }
        if(found.deadline!=-1)
        {
            out.deadline=found.deadline;
        }

    /*and return the Realtime-ness of the "call" to the user*/
        printf("VFS: Realtime: S: %d c: %d p: %d d:%d pid: %d\n",out.start_time,out.comp_time,out.period,out.deadline,out.rt_pid);
    }

  }
