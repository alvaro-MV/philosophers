#include "philo.h"

void	take_fork_log(t_philo *args)
{
	unsigned long long 	time;
	
	time = get_actual_time();
	printf("%llu %d has taken a fork", time, args->tid);
}

void	eating_log(t_philo *args)
{
	unsigned long long 	time;
	
	time = get_actual_time();
	printf("%llu %d is eating", time, args->tid);
}

void	sleeping_log(t_philo *args)
{
	unsigned long long 	time;
	
	time = get_actual_time();
	printf("%llu %d is sleeping", time, args->tid);	
}

void	thinking_log(t_philo *args)
{
	unsigned long long 	time;
	
	time = get_actual_time();
	printf("%llu %d is thinking", time, args->tid);	
}

void	died_log(t_philo *args)
{
	unsigned long long 	time;
	
	time = get_actual_time();
	printf("%llu %d is thinking", time, args->tid);	
}