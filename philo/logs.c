#include "philo.h"

void	take_fork_log(t_philo *args)
{
	unsigned long long 	time;
	
	time = get_actual_time();
	printf("%llu %d has taken a fork\n", time, args->tid + 1);
}

void	eating_log(t_philo *args)
{
	unsigned long long 	time;
	
	time = get_actual_time();
	printf("%llu %d is eating\n", time, args->tid + 1);
}

void	sleeping_log(t_philo *args)
{
	unsigned long long 	time;
	
	time = get_actual_time();
	printf("%llu %d is sleeping\n", time, args->tid + 1);	
}

void	thinking_log(t_philo *args)
{
	unsigned long long 	time;
	
	time = get_actual_time();
	printf("%llu %d is thinking\n", time, args->tid + 1);	
}

void	died_log(t_philo *args)
{
	unsigned long long 	time;
	
	time = get_actual_time();
	printf("%llu %d died\n", time, args->tid + 1);	
}