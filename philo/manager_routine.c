#include "philo.h"

void	cancel_philos(unsigned int n_philo, t_philo *arr_args)
{
	unsigned int	i;

	i = 0;

	while (i < n_philo)
	{
		printf("arr i: %d\n", arr_args[i].tid);
		write(1, "francisco Javier\n", 18);
		pthread_cancel(arr_args[i].general_vars->philo_ptrs[i]);
		i++;
	}
	free(arr_args[i].general_vars);
	free(arr_args);
}

void	*manager_routine(void *args)
{
	t_gen_var			*gen;
	t_philo				*arr_args;
	unsigned int		i;
	unsigned long long	diff_time;

	arr_args = (t_philo *) args;
	gen = arr_args->general_vars;
	printf("gen args dentro de manager: %p\n", gen);
	while (gen->philo_alive)
	{
		i = 0;
		//write(1, "\n-------Comprobacion-------------------\n\n", 42); //testeo
		pthread_mutex_lock(&arr_args[i].last_meal_mutex);
		while (i < gen->n_philo)
		{
			diff_time = get_actual_time() - arr_args[i].time_last_meal;
			//ft_putstr_fd("diff time: ", 1); //testeo
			//printf("%llu\n", diff_time); //testeo
			if (diff_time >= gen->time_to_die)
			{
				died_log(&arr_args[i]);
				cancel_philos(gen->n_philo, arr_args);
				return (NULL);
			}
			i++;
		}
		pthread_mutex_unlock(&arr_args[i].last_meal_mutex);
	}
	return (NULL);
}
