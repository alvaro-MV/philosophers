/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:40:58 by alvmoral          #+#    #+#             */
/*   Updated: 2025/01/02 13:08:26 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_routine(t_philo *args)
{
	manage_usleep(args->general_vars->time_to_sleep);
	pthread_mutex_lock(&args->general_vars->logs_mutex);
	if (!args->general_vars->philo_alive)
		return ;
	sleeping_log(args);
	pthread_mutex_unlock(&args->general_vars->logs_mutex);
}

void	think_routine(t_philo *args)
{
	manage_usleep(1);
	pthread_mutex_lock(&args->general_vars->logs_mutex);
	if (!args->general_vars->philo_alive)
		return ;
	thinking_log(args);
	if (args->n_of_meals == args->general_vars->max_meals)
	{
		args->general_vars->philo_alive--;
		args->not_dead = 0;
	}
	pthread_mutex_unlock(&args->general_vars->logs_mutex);
}

void	eat_routine(t_philo *args)
{
	t_gen_var		*gen;

	gen = args->general_vars;
	pthread_mutex_lock(&gen->logs_mutex);
	eating_log(args);
	args->time_last_meal = get_actual_time();
	args->n_of_meals++;
	pthread_mutex_unlock(&gen->logs_mutex);
	manage_usleep(gen->time_to_eat);
	pthread_mutex_lock(&gen->logs_mutex);
	if (!args->general_vars->philo_alive)
		return ;
	if (args->tid % 2)
		drop_forks(gen, args, args->tid % gen->n_philo, args->tid - 1);
	else
		drop_forks(gen, args, args->tid - 1, args->tid % gen->n_philo);
	pthread_mutex_unlock(&gen->logs_mutex);
}

static int	check_running(t_philo *args, unsigned int *i)
{
	if (args->general_vars->run_4ever)
		return (1);
	else
	{
		if (*i < args->general_vars->max_meals)
		{
			*i = *i + 1;
			return (1);
		}
		else return (0);
	}
}

void	*philo_routine(void *vargs)
{
	t_philo				*args;
	unsigned int		i;

	args = (t_philo *) vargs;
	i = 0;
	while (!args->general_vars->init_time)
		;
	args->time_last_meal = args->general_vars->init_time;
	if (args->tid % 2)
		usleep(450);
	while (1)
	{
		if (!check_running(args, &i))
			return (NULL);
		take_forks_dispatcher(args);
		eat_routine(args);
		sleep_routine(args);
		think_routine(args);
		if (!args->general_vars->philo_alive)
			break ;
	}
	return (NULL);
}
