#include "philo.h"

void	init_protection_mutexs(t_gen_var *general_vars)
{
	if (pthread_mutex_init(&general_vars->proc_mutex, NULL))
	{
		write(2, "philo: error initialization of protection mutex\n", 49);
		exit(-1);
	}
	if (pthread_mutex_init(&general_vars->logs_mutex, NULL))
	{
		write(2, "philo: error initialization of protection mutex\n", 49);
		exit(-1);
	}	
}

void	init_forks(t_gen_var *general_vars)
{
	unsigned int	i;
	unsigned int	n_philos;

	i = 0;
	n_philos = general_vars->n_philo;
	while (i < n_philos)
	{
		if (pthread_mutex_init(&general_vars->forks[i], NULL))
		{
			write(2, "philo: error initialization of forks mutex\n", 44);
			ft_free_exit(general_vars->forks_used);
		}
		i++;
	}
}

void	init_args(t_gen_var *gen_vars, t_philo *dinner, pthread_t *philo)
{
	unsigned int	n_philos;
	unsigned int	i;

	n_philos = gen_vars->n_philo;
	i = 0;
	while (i < n_philos)
	{
		dinner[i].general_vars = gen_vars;	
		dinner[i].tid = i + 1;
		dinner[i].time_last_meal = 0;
		if (pthread_mutex_init(&dinner[i].last_meal_mutex, NULL))
		{
			write(2, "philo: error  creating mutex\n", 30);
			p_free(gen_vars, dinner, philo);
		}
		i++;
	}
}