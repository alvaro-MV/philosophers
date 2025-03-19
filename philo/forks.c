/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:37:24 by alvmoral          #+#    #+#             */
/*   Updated: 2025/03/19 12:47:37by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_gen_var *gen, t_philo *args, int f1, int f2)
{
	pthread_mutex_lock(&gen->forks[f1]);
	pthread_mutex_lock(&gen->logs_mutex);
	if (!args->not_dead)
	{
		pthread_mutex_unlock(&gen->forks[f1]);
		pthread_mutex_unlock(&gen->logs_mutex);
		return (0);
	}
	fork_log(args, 1);
	pthread_mutex_unlock(&gen->logs_mutex);
	if (gen->n_philo > 1 && pthread_mutex_lock(&gen->forks[f2]))
		write(1, "", 0);
	pthread_mutex_lock(&gen->logs_mutex);
	if (!args->not_dead || args->gen_vars->n_philo == 1)
	{
		if (gen->n_philo == 1)
			manage_usleep(gen->time_to_die);
		else
			pthread_mutex_unlock(&gen->forks[f2]);
		pthread_mutex_unlock(&gen->forks[f1]);
		pthread_mutex_unlock(&gen->logs_mutex);
		return (0);
	}
	fork_log(args, 1);
	pthread_mutex_unlock(&gen->logs_mutex);
	return (1);
}

void	drop_forks(t_gen_var *gen, t_philo *args, int f1, int f2)
{
	pthread_mutex_unlock(&gen->forks[f2]);
	pthread_mutex_unlock(&gen->forks[f1]);
	pthread_mutex_lock(&gen->logs_mutex);
	if (!args->not_dead)
	{
		pthread_mutex_unlock(&gen->logs_mutex);
		return ;
	}
	fork_log(args, 0);
	fork_log(args, 0);
	pthread_mutex_unlock(&gen->logs_mutex);
}

int	take_forks_dispatcher(t_philo *dinner)
{
	t_gen_var	*gen;
	size_t		living;

	gen = dinner->gen_vars;
	if (dinner->tid % 2)
		living = take_forks(gen, dinner, dinner->tid % gen->n_philo, dinner->tid
				- 1);
	else
		living = take_forks(gen, dinner, dinner->tid - 1, dinner->tid
				% gen->n_philo);
	return (living);
}
