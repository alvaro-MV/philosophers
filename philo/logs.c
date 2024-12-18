#include "philo.h"

void	fork_log(t_philo *args, size_t action)
{
	unsigned long long	time;

	time = get_actual_time();
	//testeo
	unsigned long long usecs = time / 10000;
	usecs *= 10000;
	time -= usecs;
	//testeo
	if (action)
		ft_printf("\033[3;33m%l %d has taken a fork\n", time, args->tid);
	else
		ft_printf("\033[3;36m%l %d has release a forks\n", time, args->tid);
}

void	eating_log(t_philo *args)
{
	unsigned long long	time;

	time = get_actual_time();
	//testeo
	unsigned long long usecs = time / 10000;
	usecs *= 10000;
	time -= usecs;
	//testeo
	ft_printf("\033[3;32m%l %d is eating\n", time, args->tid);
}

void	sleeping_log(t_philo *args)
{
	unsigned long long	time;

	time = get_actual_time();
	//testeo
	unsigned long long usecs = time / 10000;
	usecs *= 10000;
	time -= usecs;
	//testeo
	ft_printf("\033[3;35m%l %d is sleeping\n", time, args->tid);	
}

void	thinking_log(t_philo *args)
{
	unsigned long long	time;

	time = get_actual_time();
	//testeo
	unsigned long long usecs = time / 10000;
	usecs *= 10000;
	time -= usecs;
	//testeo
	ft_printf("\033[3;34m%l %d is thinking\n", time, args->tid);	
}

void	died_log(t_philo *args)
{
	unsigned long long	time;

	time = get_actual_time();
	//testeo
	unsigned long long usecs = time / 10000;
	usecs *= 10000;
	time -= usecs;
	//testeo
	ft_printf("\033[3;31m%l %d died\n\033[0m", time, args->tid);	
}
