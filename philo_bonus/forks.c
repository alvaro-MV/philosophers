/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:37:24 by alvmoral          #+#    #+#             */
/*   Updated: 2025/02/17 12:12:10 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_gen_var *gen, t_philo *args, int f1, int f2)
{
	(void) f1;
	(void) f2;
	sem_wait(gen->forks);
	sem_wait(gen->logs_sem);
	fork_log(args, 1);
	sem_post(gen->logs_sem);
	sem_wait(gen->forks);
	sem_wait(gen->logs_sem);
	if (args->gen_vars->n_philo == 1)
	{
		sem_post(gen->forks);
		sem_post(gen->forks);
		return ;
	}
	fork_log(args, 1);
	sem_post(gen->logs_sem);
}

void	drop_forks(t_gen_var *gen, t_philo *args, int f1, int f2)
{
	(void) f1;
	(void) f2;
	sem_post(gen->forks);
	fork_log(args, 0);
	sem_post(gen->forks);
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
