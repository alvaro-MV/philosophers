/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:41:04 by alvmoral          #+#    #+#             */
/*   Updated: 2025/02/17 13:22:36 by alvmoral         ###   ########.fr       */
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
		since_last_meal = time_diff_usecs(dinner->time_last_meal);
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
