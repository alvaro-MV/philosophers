#include "philo.h"

void	cancel_philos(unsigned int n_philo, t_philo *arr_args)
{
	unsigned int	i;

	i = 0;

	while (i < n_philo)
	{
		pthread_cancel(arr_args[i].thread_ptr);
		p_free(&arr_args[i].general_vars, arr_args, &arr_args->thread_ptr);
		i++;
	}
}

void	*manager_routine(void *args)
{
	t_general_vars		gen;
	t_philo				*arr_args;
	unsigned int		i;
	unsigned long long	diff_time;

	i = 0;
	arr_args = (t_philo *) args;
	gen = arr_args->general_vars;
	while (i < gen.n_philo)
	{
		diff_time = get_actual_time() - arr_args[i].time_last_meal;
		if (diff_time >= gen.time_to_die)
		{
			died_log(&arr_args[i]);
			cancel_philos(gen.n_philo, arr_args);
		}
		i++;
	}
	return (NULL);
}