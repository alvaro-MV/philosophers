/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:41:04 by alvmoral          #+#    #+#             */
/*   Updated: 2025/02/12 00:15:45by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*manager_routine(void *vargs)
{
	t_philo 	*dinner;
	t_gen_var	*gen_vars;
	uint64_t	since_last_meal;
	uint64_t	control;
	
	dinner = (t_philo *) vargs;
	gen_vars = dinner->gen_vars;
	while (dinner->not_dead)
	{
		since_last_meal = time_diff_usecs(dinner->time_last_meal);
		control = get_actual_time() - dinner->time_last_meal;
		if (since_last_meal >= gen_vars->time_to_die)
		{
			if (control >= gen_vars->time_to_die)
			{
				sem_wait(dinner->gen_vars->logs_sem);
				died_log(dinner);
				printf("since last meal: %lu   control: %lu \n", since_last_meal, control); //testeo
				dinner->not_dead = 0;
				exit(9);
			}
		}
	}
	return (NULL);
}
