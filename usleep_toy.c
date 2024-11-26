#include "philo/philo.h"

int	main(void)
{
	unsigned long long start = get_actual_time();
	manage_usleep(2399999);
	unsigned long long final = get_actual_time();
	printf("start: %llu\tfinal: %llu\ndiff: %llu\n", start, final, time_diff_usecs(start));
}