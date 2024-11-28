/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:40:58 by alvmoral          #+#    #+#             */
/*   Updated: 2024/11/27 18:09:21 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_routine(t_philo *args)
{
	manage_usleep(args->general_vars->time_to_sleep);
	pthread_mutex_lock(&args->general_vars->logs_mutex);
	sleeping_log(args);
	pthread_mutex_unlock(&args->general_vars->logs_mutex);
}

void	think_routine(t_philo *args)
{
	usleep(1); //Thinking que pongo weyyy
	pthread_mutex_lock(&args->general_vars->logs_mutex);
	thinking_log(args);
	if (args->n_of_meals == args->general_vars->max_meals)
	{
		args->general_vars->philo_alive--;
		pthread_mutex_unlock(&args->general_vars->logs_mutex);
		// pthread_join(philo[args->tid - 1], NULL);
	}
	pthread_mutex_unlock(&args->general_vars->logs_mutex);
}


void	eat_routine(t_philo *args)
{
	t_gen_var		*gen;
	pthread_t		*philo;

	gen = args->general_vars;
	philo = args->general_vars->philo_ptrs;

	manage_usleep(gen->time_to_eat);
	pthread_mutex_lock(&gen->logs_mutex);
	eating_log(args);
	args->time_last_meal = get_actual_time();
	args->n_of_meals++;
	pthread_mutex_unlock(&gen->forks[args->tid - 1]);
	pthread_mutex_unlock(&gen->forks[args->tid  % gen->n_philo]);

	pthread_mutex_unlock(&gen->logs_mutex);
}

void	take_forks(t_philo *args)
{
	t_gen_var		*gen;

	gen = args->general_vars;
	if (args->tid % 2 != 0)
		manage_usleep(WAI_T);
	if (args->tid == 0)
	{
		pthread_mutex_lock(&gen->forks[args->tid % gen->n_philo]);
		pthread_mutex_lock(&gen->logs_mutex);
		take_fork_log(args);
		pthread_mutex_unlock(&gen->logs_mutex);

		pthread_mutex_lock(&gen->forks[args->tid - 1]);
		pthread_mutex_lock(&gen->logs_mutex);
		take_fork_log(args);
		pthread_mutex_unlock(&gen->logs_mutex);
	}
	else
	{
		pthread_mutex_lock(&gen->forks[args->tid - 1]);
		pthread_mutex_lock(&args->general_vars->logs_mutex);
		take_fork_log(args);
		pthread_mutex_unlock(&args->general_vars->logs_mutex);

		pthread_mutex_lock(&gen->forks[args->tid % gen->n_philo]);
		pthread_mutex_lock(&args->general_vars->logs_mutex);
		take_fork_log(args);
		pthread_mutex_unlock(&args->general_vars->logs_mutex);
	}
}

static int	check_running(t_philo *args, int *i)
{
	if (args->general_vars->run_4ever) return (1);
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
	unsigned long long	timestamp;
	int					i;

	args = (t_philo *) vargs;
	i = 0;
	while (check_running(args, &i))
	{
		take_forks(args);
		eat_routine(args);
		sleep_routine(args);
		think_routine(args);
	}
	return (NULL);
}
