/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:37:24 by alvmoral          #+#    #+#             */
/*   Updated: 2025/03/06 17:51:55 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_gen_var *gen, t_philo *args, int f1, int f2)
{
	pthread_mutex_lock(&gen->forks[f1]);
	if (!args->not_dead)
		return ;
	pthread_mutex_lock(&gen->logs_mutex);
	if (!args->not_dead)
	{
		pthread_mutex_unlock(&gen->forks[f1]);
		pthread_mutex_unlock(&gen->logs_mutex);
		return ;
	}
	fork_log(args, 1);
	pthread_mutex_unlock(&gen->logs_mutex);

	pthread_mutex_lock(&gen->forks[f2]);
	if (!args->not_dead)
	{
		pthread_mutex_unlock(&gen->forks[f1]);
		pthread_mutex_unlock(&gen->logs_mutex);
		return ;
	}
	pthread_mutex_lock(&gen->logs_mutex);
	if (args->gen_vars->n_philo == 1)
	{
		pthread_mutex_unlock(&gen->forks[f2]);
		pthread_mutex_unlock(&gen->forks[f1]);
		return ;
	}
	fork_log(args, 1);
	pthread_mutex_unlock(&gen->logs_mutex);
}

void	drop_forks(t_gen_var *gen, t_philo *args, int f1, int f2)
{
	pthread_mutex_unlock(&gen->forks[f1]);
	fork_log(args, 0);
	pthread_mutex_unlock(&gen->forks[f2]);
	fork_log(args, 0);
}

void	take_forks_dispatcher(t_philo *dinner)
{
	t_gen_var		*gen;

	gen = dinner->gen_vars;
	if (dinner->tid % 2)
		take_forks(gen, dinner, dinner->tid % gen->n_philo, dinner->tid - 1);
	else
		take_forks(gen, dinner, dinner->tid - 1, dinner->tid % gen->n_philo);
}
