#include "philo.h"

void	cancel_philos(unsigned int n_philo, t_philo *arr_args)
{
	unsigned int	i;

	i = 0;
	pthread_mutex_lock(&arr_args->last_meal_mutex);
	while (i < n_philo)
	{
		pthread_join(arr_args[i].general_vars->philo_ptrs[i], NULL);
		write(1, "Esto tira??\n", 13);
		i++;
	}
	pthread_mutex_unlock(&arr_args->last_meal_mutex);
}

void	*manager_routine(void *args)
{
	t_gen_var			*gen;
	t_philo				*arr_args;
	unsigned int		i;
	unsigned long long	diff_time;

	write(1, "entra en manageeeeeeeeeer\n", 27);
	arr_args = (t_philo *) args;
	gen = arr_args->general_vars;
	while (gen->philo_alive)
	{
		i = 0;
		pthread_mutex_lock(&arr_args->general_vars->logs_mutex);
		write(1, "\n-------Comprobacion-------------------\n\n", 42); //testeo
		while (i < gen->n_philo)
		{
			diff_time = time_diff_usecs(arr_args[i].time_last_meal);
			ft_putstr_fd("diff time: ", 1); //testeo
			printf("%llu\n", diff_time); //testeo
			if (diff_time >= gen->time_to_die)
			{
				died_log(&arr_args[i]);
				cancel_philos(gen->n_philo, arr_args);
				pthread_mutex_unlock(&arr_args->general_vars->logs_mutex);
				return (NULL);
			}
			i++;
		}
		pthread_mutex_unlock(&arr_args->general_vars->logs_mutex);
		write(1, "\n--------------------------------------\n\n", 42); //testeo
	}
	return (NULL);
}
