#include "philo.h"

void	take_fork_log(unsigned long long timestamp, t_philo *args)
{
	printf("%llu %d has taken a fork", get_timestamp(timestamp), args->tid);
}

void	eating_log(unsigned long long timestamp, t_philo *args)
{
	printf("%llu %d is eating", get_timestamp(timestamp), args->tid);	
}

void	sleeping_log(unsigned long long timestamp, t_philo *args)
{
	printf("%llu %d is sleeping", get_timestamp(timestamp), args->tid);	
}

void	thinking_log(unsigned long long timestamp, t_philo *args)
{
	printf("%llu %d is thinking", get_timestamp(timestamp), args->tid);	
}

void	died_log(unsigned long long timestamp, t_philo *args)
{
	printf("%llu %d is thinking", get_timestamp(timestamp), args->tid);	
}