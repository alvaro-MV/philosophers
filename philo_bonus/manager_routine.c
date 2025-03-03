/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:41:04 by alvmoral          #+#    #+#             */
/*   Updated: 2025/03/03 18:04:44 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*manager_routine(void *vargs)
{
	t_philo		*dinner;
	t_gen_var	*gen_vars;
	uint64_t	since_last_meal;

	dinner = (t_philo *) vargs;
	gen_vars = dinner->gen_vars;
	while (dinner->not_dead)
	{
		sem_wait(dinner->gen_vars->logs_sem);
		sem_wait(dinner->gen_vars->last_meal_mutex);
		since_last_meal = time_diff_usecs(dinner->time_last_meal);
		sem_post(dinner->gen_vars->last_meal_mutex);
		if (since_last_meal >= gen_vars->time_to_die)
		{
			died_log(dinner);
			dinner->not_dead = 0;
			exit(9);
		}
		sem_post(dinner->gen_vars->logs_sem);
	}
	return (NULL);
}
