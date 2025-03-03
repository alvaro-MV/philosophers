/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:41:04 by alvmoral          #+#    #+#             */
/*   Updated: 2025/03/03 15:52:44 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_died_routine(t_philo *arr_dinner, pthread_t *philo, int i)
{
	died_log(&arr_dinner[i]);
	// pthread_mutex_unlock(&arr_dinner->gen_vars->death_mutex);
	// pthread_mutex_unlock(&arr_dinner->gen_vars->logs_mutex);
	free(arr_dinner->gen_vars->forks_used);
	free(arr_dinner->gen_vars->forks);
	ft_free_exit(philo);
	return (NULL);
}

void	*manager_routine(void *vargs, pthread_t *philo)
{
	t_gen_var		*gen;
	t_philo			*arr_dinner;
	unsigned int	i;
	uint64_t		diff_time;

	arr_dinner = (t_philo *) vargs;
	gen = arr_dinner->gen_vars;
	while (1)
	{
		i = 0;
		pthread_mutex_lock(&arr_dinner->gen_vars->death_mutex);
		if (!gen->philo_alive)
			break ;
		pthread_mutex_unlock(&arr_dinner->gen_vars->death_mutex);
		manage_usleep(&arr_dinner->gen_vars->logs_mutex, WAI_T);
		pthread_mutex_lock(&arr_dinner->gen_vars->logs_mutex);
		while (i < gen->n_philo && arr_dinner[i].not_dead)
		{
			pthread_mutex_lock(&arr_dinner->gen_vars->death_mutex);
			diff_time = time_diff_usecs(arr_dinner[i].time_last_meal);
			if (diff_time >= gen->time_to_die)
			{
				arr_dinner[i].not_dead = 0;
				gen->philo_alive--;
				philo_died_routine(arr_dinner, philo, i);
				return (NULL);
			}
			i++;
			pthread_mutex_unlock(&arr_dinner->gen_vars->death_mutex);
		}
		pthread_mutex_unlock(&arr_dinner->gen_vars->logs_mutex);
	}
	wait_philos(arr_dinner, philo);
	return (NULL);
}
