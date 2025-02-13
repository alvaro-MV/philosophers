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
	
	dinner = (t_philo *) vargs;
	gen_vars = dinner->gen_vars;
	while (gen_vars->philo_alive)
	{
		if (time_diff_usecs(dinner->time_last_meal) >= gen_vars->time_to_die)
		{
			sem_wait(dinner->gen_vars->logs_sem);
			died_log(dinner);
			dinner->not_dead = 0;
			// sem_post(dinner->gen_vars->logs_sem);
			// kill(dinner->pid, SIGKILL);
			exit(9);
			return (vargs);
		}
	}
	return (NULL);
}
