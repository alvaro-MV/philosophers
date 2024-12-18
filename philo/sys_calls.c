#include "philo.h"
#include <unistd.h>

void	manage_usleep(__useconds_t	miliseconds)
{
	unsigned long long	start;

	start = get_actual_time();
	while (get_actual_time() < start + miliseconds)
		usleep(9);
}

// int	main(void)
// {
// 	unsigned long long	tmp;
// 	unsigned long long	print;

// 	tmp = get_actual_time(); 
// 	print = tmp - ((tmp / 10000) * 10000);
// 	printf("before: %llu\n", print);
// 	manage_usleep(56);
// 	tmp = get_actual_time(); 
// 	print = tmp - ((tmp / 10000) * 10000);
// 	printf("after: %llu\n", print);
// }
