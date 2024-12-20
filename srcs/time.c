#include "../includes/flap.h"

unsigned long	get_time()
{
	t_timeval	end;

	gettimeofday(&end, 0);
	return ((end.tv_sec * 1000000) + end.tv_usec);
}

unsigned long	get_timediff(unsigned long start)
{
	unsigned long	end;
	
	end = get_time();
	return (end - start);
}
