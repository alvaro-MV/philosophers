#include "philo.h"

void	take_fork_log(t_philo *args)
{
	unsigned long long 	time;
	
	time = get_actual_time();
	//testeo
	unsigned long long usecs = time / 10000;
	usecs *= 10000;
	time -= usecs;
	//testeo
	ft_printf("\033[3;33m%l [%d] has taken a fork\n", time, args->tid);
}

void	eating_log(t_philo *args)
{
	unsigned long long 	time;
	
	time = get_actual_time();
	//testeo
	unsigned long long usecs = time / 10000;
	usecs *= 10000;
	time -= usecs;
	//testeo
	ft_printf("\033[3;32m%l [%d] is eating\n", time, args->tid);
}

void	sleeping_log(t_philo *args)
{
	unsigned long long 	time;
	
	time = get_actual_time();
	//testeo
	unsigned long long usecs = time / 10000;
	usecs *= 10000;
	time -= usecs;
	//testeo
	ft_printf("\033[3;35m%l [%d] is sleeping\n", time, args->tid);	
}

void	thinking_log(t_philo *args)
{
	unsigned long long 	time;
	
	time = get_actual_time();
	//testeo
	unsigned long long usecs = time / 10000;
	usecs *= 10000;
	time -= usecs;
	//testeo
	ft_printf("\033[3;34m%l [%d] is thinking\n", time, args->tid);	
}

void	died_log(t_philo *args)
{
	unsigned long long 	time;
	
	time = get_actual_time();
	//testeo
	unsigned long long usecs = time / 10000;
	usecs *= 10000;
	time -= usecs;
	//testeo
	ft_printf("\033[3;31m%l [%d] died\n", time, args->tid);	
}