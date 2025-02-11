/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:41:04 by alvmoral          #+#    #+#             */
/*   Updated: 2025/02/11 20:50:31 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_died_routine(t_philo *arr_dinner, int i)
{
	died_log(&arr_dinner[i]);
	wait_philos(arr_dinner);
	sem_post(arr_dinner->gen_vars->logs_sem);
	return (NULL);
}

void	*manager_routine(void *vargs)
{
	t_gen_var		*gen;
	t_philo			*arr_dinner;
	unsigned int	i;
	uint64_t		diff_time;

	arr_dinner = (t_philo *) vargs;
	gen = arr_dinner->gen_vars;
	while (gen->philo_alive)
	{
		i = 0;
		manage_usleep(arr_dinner->gen_vars->logs_sem, WAI_T);
		sem_wait(arr_dinner->gen_vars->logs_sem);
		while (i < gen->n_philo && arr_dinner[i].not_dead)
		{
			diff_time = time_diff_usecs(arr_dinner[i].time_last_meal);
			if (diff_time >= gen->time_to_die)
				return (philo_died_routine(arr_dinner, i));
			i++;
		}
		sem_post(arr_dinner->gen_vars->logs_sem);
	}
	wait_philos(arr_dinner);
	return (NULL);
}
