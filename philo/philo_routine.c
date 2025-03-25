/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:40:58 by alvmoral          #+#    #+#             */
/*   Updated: 2025/03/25 15:13:06 by alvmoral         ###   ########.fr       */
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
	pthread_mutex_unlock(&dinner->gen_vars->logs_mutex);
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

void	_philo_routine(t_philo *dinner)
{
	eat_routine(dinner);
	sleep_routine(dinner);
	think_routine(dinner);
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
		_philo_routine(dinner);
	}
	pthread_mutex_lock(&dinner->gen_vars->logs_mutex);
	dinner->th_finish = 1;
	pthread_mutex_unlock(&dinner->gen_vars->logs_mutex);
	return (NULL);
}
