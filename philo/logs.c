#include "philo.h"

void	take_fork_log(unsigned long long timestamp, t_philo *args)
{
	printf("%llu %d has taken a fork", time_diff_usecs(timestamp), args->tid);
}

void	eating_log(unsigned long long timestamp, t_philo *args)
{
	printf("%llu %d is eating", time_diff_usecs(timestamp), args->tid);
}

void	sleeping_log(unsigned long long timestamp, t_philo *args)
{
	printf("%llu %d is sleeping", time_diff_usecs(timestamp), args->tid);	
}

void	thinking_log(unsigned long long timestamp, t_philo *args)
{
	printf("%llu %d is thinking", time_diff_usecs(timestamp), args->tid);	
}

void	died_log(unsigned long long timestamp, t_philo *args)
{
	printf("%llu %d is thinking", time_diff_usecs(timestamp), args->tid);	
}