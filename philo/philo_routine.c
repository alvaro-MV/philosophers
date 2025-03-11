/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:40:58 by alvmoral          #+#    #+#             */
/*   Updated: 2025/03/11 14:08:53 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_routine(t_philo *dinner)
{
	manage_usleep(dinner->gen_vars->time_to_sleep);
	pthread_mutex_lock(&dinner->gen_vars->logs_mutex);
	if (!dinner->not_dead)
	{
		pthread_mutex_unlock(&dinner->gen_vars->logs_mutex);
		return ;
	}	
	pthread_mutex_unlock(&dinner->gen_vars->logs_mutex);
	pthread_mutex_lock(&dinner->gen_vars->logs_mutex);
	sleeping_log(dinner);
	pthread_mutex_unlock(&dinner->gen_vars->logs_mutex);
}

void	think_routine(t_philo *dinner)
{

	pthread_mutex_lock(&dinner->gen_vars->logs_mutex);
	if (!dinner->not_dead)
	{
		pthread_mutex_unlock(&dinner->gen_vars->logs_mutex);
		return ;
	}	
	thinking_log(dinner);
	if (dinner->n_of_meals == dinner->gen_vars->max_meals)
	{
		dinner->gen_vars->philo_alive--;
		dinner->not_dead = 0;
	}
	pthread_mutex_unlock(&dinner->gen_vars->logs_mutex);
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
			drop_forks(gen, dinner, dinner->tid % gen->n_philo, dinner->tid - 1);
		}
		else
		{
			pthread_mutex_unlock(&dinner->gen_vars->logs_mutex);
			drop_forks(gen, dinner, dinner->tid - 1, dinner->tid % gen->n_philo);
		}
		return ;
	}
	if (dinner->not_dead)
	{
		dinner->time_last_meal = get_actual_time();
		dinner->n_of_meals++;
		eating_log(dinner);
	}
	pthread_mutex_unlock(&dinner->gen_vars->logs_mutex);
	if (dinner->not_dead)
		manage_usleep(dinner->gen_vars->time_to_eat);
	if (dinner->tid % 2)
		drop_forks(gen, dinner, dinner->tid % gen->n_philo, dinner->tid - 1);
	else
		drop_forks(gen, dinner, dinner->tid - 1, dinner->tid % gen->n_philo);
}

static int	check_running(t_philo *dinner, unsigned int *i)
{
	pthread_mutex_lock(&dinner->gen_vars->logs_mutex);
	if (!dinner->not_dead)
	{
		pthread_mutex_unlock(&dinner->gen_vars->logs_mutex);
		return (0);
	}
	pthread_mutex_unlock(&dinner->gen_vars->logs_mutex);
	if (dinner->gen_vars->run_4ever)
		return (1);
	else
	{
		if (*i < dinner->gen_vars->max_meals)
		{
			*i = *i + 1;
			return (1);
		}
		else
			return (0);
	}
}

void	*philo_routine(void *vargs)
{
	t_philo			*dinner;
	unsigned int	i;

	dinner = init_philo_routine(vargs, &i);
	while (1)
	{
		pthread_mutex_lock(&dinner->gen_vars->logs_mutex);
		if (!dinner->not_dead)
		{
			pthread_mutex_unlock(&dinner->gen_vars->logs_mutex);
			break ;
		}	
		pthread_mutex_unlock(&dinner->gen_vars->logs_mutex);
		if (!check_running(dinner, &i))
			break ;
		if (dinner->tid % 2)
			usleep(450);
		if (!take_forks_dispatcher(dinner))
			break ;
		eat_routine(dinner);
		sleep_routine(dinner);
		think_routine(dinner);
	}
	pthread_mutex_lock(&dinner->gen_vars->logs_mutex);
	dinner->th_finish = 1;
	pthread_mutex_unlock(&dinner->gen_vars->logs_mutex);
	return (NULL);
}
