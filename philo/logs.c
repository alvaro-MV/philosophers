#include "philo.h"

void	fork_log(t_philo *dinner, size_t action)
{
	uint64_t	time;

	time = get_actual_time();
	time = time - dinner->gen_vars->init_time + 1;
	if (action)
		ft_printf("\033[3;33m%l %d has taken a fork\n", time, dinner->tid);
	else
		ft_printf("\033[3;36m%l %d has release a forks\n", time, dinner->tid);
}

void	eating_log(t_philo *dinner)
{
	uint64_t	time;

	time = get_actual_time();
	time = time - dinner->gen_vars->init_time + 1;
	ft_printf("\033[3;32m%l %d is eating\n", time, dinner->tid);
}

void	sleeping_log(t_philo *dinner)
{
	uint64_t	time;

	time = get_actual_time();
	time = time - dinner->gen_vars->init_time + 1;
	ft_printf("\033[3;35m%l %d is sleeping\n", time, dinner->tid);	
}

void	thinking_log(t_philo *dinner)
{
	uint64_t	time;

	time = get_actual_time();
	time = time - dinner->gen_vars->init_time + 1;
	ft_printf("\033[3;34m%l %d is thinking\n", time, dinner->tid);	
}

void	died_log(t_philo *dinner)
{
	uint64_t	time;

	time = get_actual_time();
	time = time - dinner->gen_vars->init_time + 1;
	ft_printf("\033[3;31m%l %d died\n\033[0m", time, dinner->tid);	
}
