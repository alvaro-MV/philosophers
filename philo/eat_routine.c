/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:07:43 by alvmoral          #+#    #+#             */
/*   Updated: 2025/03/19 13:13:34 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eating(t_philo *dinner)
{
	if (dinner->not_dead)
	{
		pthread_mutex_lock(&dinner->last_meal_mutex);
		dinner->time_last_meal = get_actual_time();
		dinner->n_of_meals++;
		eating_log(dinner);
		pthread_mutex_unlock(&dinner->last_meal_mutex);
	}
}

void	drop_forks_after_eat(t_gen_var *gen, t_philo *dinner)
{
	if (dinner->tid % 2)
		drop_forks(gen, dinner, dinner->tid % gen->n_philo, dinner->tid - 1);
	else
		drop_forks(gen, dinner, dinner->tid - 1, dinner->tid % gen->n_philo);
}

void	eat_routine(t_philo *dinner)
{
	t_gen_var		*gen;

	gen = dinner->gen_vars;
	pthread_mutex_lock(&dinner->gen_vars->logs_mutex);
	if (!dinner->not_dead)
	{
		if (dinner->tid % 2)
		{
			pthread_mutex_unlock(&dinner->gen_vars->logs_mutex);
			drop_forks(dinner->gen_vars, dinner,
				dinner->tid % dinner->gen_vars->n_philo, dinner->tid - 1);
		}
		else
		{
			pthread_mutex_unlock(&dinner->gen_vars->logs_mutex);
			drop_forks(dinner->gen_vars, dinner, dinner->tid - 1,
				dinner->tid % dinner->gen_vars->n_philo);
		}
		return ;
	}
	philo_eating(dinner);
	pthread_mutex_unlock(&dinner->gen_vars->logs_mutex);
	manage_usleep(dinner->gen_vars->time_to_eat);
	drop_forks_after_eat(gen, dinner);
}
