/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:42:54 by alvmoral          #+#    #+#             */
/*   Updated: 2025/03/25 14:42:55 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	died_routine(t_philo *dinner)
{
	died_log(dinner);
	sem_wait(dinner->gen_vars->last_meal_mutex);
	dinner->not_dead = 0;
	sem_post(dinner->gen_vars->last_meal_mutex);
	exit(9);
}

void	*manager_routine(void *vargs)
{
	t_philo		*dinner;
	t_gen_var	*gen_vars;
	uint64_t	since_last_meal;

	dinner = (t_philo *) vargs;
	gen_vars = dinner->gen_vars;
	while (1)
	{
		sem_wait(dinner->gen_vars->last_meal_mutex);
		if (!dinner->not_dead)
		{
			sem_post(dinner->gen_vars->last_meal_mutex);
			break ;
		}
		sem_post(dinner->gen_vars->last_meal_mutex);
		sem_wait(dinner->gen_vars->logs_sem);
		sem_wait(dinner->gen_vars->last_meal_mutex);
		since_last_meal = time_diff_usecs(dinner->time_last_meal);
		sem_post(dinner->gen_vars->last_meal_mutex);
		if (since_last_meal >= gen_vars->time_to_die)
			died_routine(dinner);
		sem_post(dinner->gen_vars->logs_sem);
	}
	return (NULL);
}
