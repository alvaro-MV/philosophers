/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:40:58 by alvmoral          #+#    #+#             */
/*   Updated: 2025/03/07 18:53:28 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_routine(t_philo *dinner)
{
	pthread_mutex_lock(&dinner->gen_vars->death_mutex);
	if (!dinner->not_dead)
		return ;
	pthread_mutex_unlock(&dinner->gen_vars->death_mutex);
	manage_usleep(dinner->gen_vars->time_to_sleep);
	pthread_mutex_lock(&dinner->gen_vars->logs_mutex);
	if (!dinner->gen_vars->philo_alive)
		return ;
	sleeping_log(dinner);
	pthread_mutex_unlock(&dinner->gen_vars->logs_mutex);
}

void	think_routine(t_philo *dinner)
{
	if (!dinner->not_dead)
		return ;
	pthread_mutex_lock(&dinner->gen_vars->logs_mutex);
	if (!dinner->gen_vars->philo_alive)
		return ;
	thinking_log(dinner);
	pthread_mutex_lock(&dinner->gen_vars->death_mutex);
	if (dinner->n_of_meals == dinner->gen_vars->max_meals)
	{
		dinner->gen_vars->philo_alive--;
		dinner->not_dead = 0;
	}
	pthread_mutex_unlock(&dinner->gen_vars->death_mutex);
	pthread_mutex_unlock(&dinner->gen_vars->logs_mutex);
}

void	eat_routine(t_philo *dinner)
{
	t_gen_var		*gen;

	gen = dinner->gen_vars;
	if (!dinner->not_dead)
	{
		pthread_mutex_lock(&gen->logs_mutex);
		if (!dinner->gen_vars->philo_alive)
			return ;
		if (dinner->tid % 2)
			drop_forks(gen, dinner, dinner->tid % gen->n_philo, dinner->tid - 1);
		else
			drop_forks(gen, dinner, dinner->tid - 1, dinner->tid % gen->n_philo);
		pthread_mutex_unlock(&gen->logs_mutex);
		return ;
	}
	pthread_mutex_lock(&gen->logs_mutex);
	pthread_mutex_lock(&gen->death_mutex);
	eating_log(dinner);
	dinner->time_last_meal = get_actual_time();
	dinner->n_of_meals++;
	pthread_mutex_unlock(&gen->death_mutex);
	pthread_mutex_unlock(&gen->logs_mutex);
	manage_usleep(gen->time_to_eat);
	
	pthread_mutex_lock(&gen->logs_mutex);
	if (!dinner->gen_vars->philo_alive)
		return ;
	if (dinner->tid % 2)
		drop_forks(gen, dinner, dinner->tid % gen->n_philo, dinner->tid - 1);
	else
		drop_forks(gen, dinner, dinner->tid - 1, dinner->tid % gen->n_philo);
	pthread_mutex_unlock(&gen->logs_mutex);
}

static int	check_running(t_philo *dinner, unsigned int *i)
{
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
		pthread_mutex_lock(&dinner->gen_vars->death_mutex);
		if (!dinner->not_dead)
		{
			pthread_mutex_unlock(&dinner->gen_vars->death_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&dinner->gen_vars->death_mutex);
		if (!check_running(dinner, &i))
			return (NULL);
		if (dinner->tid % 2)
			usleep (4500);
		take_forks_dispatcher(dinner);
		eat_routine(dinner);
		sleep_routine(dinner);
		think_routine(dinner);
		pthread_mutex_lock(&dinner->gen_vars->death_mutex);
		if (!dinner->gen_vars->philo_alive)
		{
			pthread_mutex_unlock(&dinner->gen_vars->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&dinner->gen_vars->death_mutex);
	}
	return (NULL);
}
