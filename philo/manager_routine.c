/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:41:04 by alvmoral          #+#    #+#             */
/*   Updated: 2025/03/11 11:56:31alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_died_routine(t_philo *arr_dinner, pthread_t *philo, int i)
{
	(void) philo;
	died_log(&arr_dinner[i]);
	return (NULL);
}

int	check_liveness(t_philo *arr_dinner, unsigned int *i, pthread_t *philo)
{
	uint64_t		diff_time;
	size_t			j;
	size_t			stop;

	j = 0;
	stop = 1;
	while (j < arr_dinner->gen_vars->n_philo && stop)
	{
		stop = arr_dinner[j].n_of_meals >= arr_dinner[j].gen_vars->max_meals;
		j++;
	}
	if (stop)
		return (0);
	j = 0;
	diff_time = time_diff_usecs(arr_dinner[*i].time_last_meal);
	if (diff_time >= arr_dinner[*i].gen_vars->time_to_die)
	{
		while (j < arr_dinner->gen_vars->n_philo)
		{
			arr_dinner[j].not_dead = 0;
			j++;
		}
		j = 0;
		while (j < arr_dinner->gen_vars->n_philo)
			pthread_detach(philo[j++]);
		arr_dinner->gen_vars->philo_alive--;
		philo_died_routine(arr_dinner, philo, *i);
		return (0);
	}
	return (1);
}

void	*manager_routine(void *vargs, pthread_t *philo)
{
	t_gen_var		*gen;
	t_philo			*arr_dinner;
	unsigned int	i;
	unsigned int	n_dead;

	arr_dinner = (t_philo *) vargs;
	gen = arr_dinner->gen_vars;
	n_dead = 0;
	while (1)
	{
		if (n_dead == gen->n_philo)
			break ;
		n_dead = 0;
		i = 0;
		manage_usleep(WAI_T);
		while (i < gen->n_philo)
		{
			pthread_mutex_lock(&arr_dinner->gen_vars->logs_mutex);
			if (arr_dinner[i].not_dead && !check_liveness(arr_dinner, &i, philo))
			{
				n_dead = gen->n_philo;
				pthread_mutex_unlock(&arr_dinner->gen_vars->logs_mutex);
				break ;
			}
			if (!arr_dinner[i].not_dead)
				n_dead++;
			i++;
			pthread_mutex_unlock(&arr_dinner->gen_vars->logs_mutex);
		}
	}
	wait_philos(arr_dinner, philo);
	return (NULL);
}
