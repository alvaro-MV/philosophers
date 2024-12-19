/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:41:04 by alvmoral          #+#    #+#             */
/*   Updated: 2024/12/19 11:31:48 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*manager_routine(void *args, pthread_t *philo)
{
	t_gen_var			*gen;
	t_philo				*arr_args;
	unsigned int		i;
	unsigned long long	diff_time;

	arr_args = (t_philo *) args;
	gen = arr_args->general_vars;
	while (gen->philo_alive)
	{
		i = 0;
		manage_usleep(WAI_T);
		pthread_mutex_lock(&arr_args->general_vars->logs_mutex);
		while (i < gen->n_philo && arr_args->not_dead)
		{
			diff_time = time_diff_usecs(arr_args[i].time_last_meal);
			// ft_printf("philo_alive: %u\n", gen->philo_alive); //testeo
			if (diff_time >= gen->time_to_die)
			{
				died_log(&arr_args[i]);
				wait_philos(args, philo);
				pthread_mutex_unlock(&arr_args->general_vars->logs_mutex);
				return (NULL);
			}
			i++;
		}
		pthread_mutex_unlock(&arr_args->general_vars->logs_mutex);
	}
	wait_philos(args, philo);
	return (NULL);
}
