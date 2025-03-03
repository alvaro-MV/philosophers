/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:40:54 by alvmoral          #+#    #+#             */
/*   Updated: 2025/03/03 18:06:01 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_protection_sem(t_gen_var *gen_vars)
{
	sem_unlink("/logs_sem");
	gen_vars->logs_sem = sem_open("/logs_sem", O_CREAT, S_IRUSR, 1);
	if (gen_vars->logs_sem == SEM_FAILED)
	{
		write(2, "philo: error initialization of logs sem.\n", 42);
		return (0);
	}
	sem_unlink("/last_meal_sem");
	gen_vars->last_meal_mutex = sem_open("/last_meal_sem", O_CREAT, S_IRUSR, 1);
	if (gen_vars->last_meal_mutex == SEM_FAILED)
	{
		write(2, "philo: error initialization of logs sem.\n", 42);
		return (0);
	}
	return (1);
}

int	init_forks(t_gen_var *gen_vars)
{
	sem_unlink("/forks");
	gen_vars->forks = sem_open("/forks", O_CREAT, S_IRUSR, gen_vars->n_philo);
	if (gen_vars->forks == SEM_FAILED)
		return (sem_close(gen_vars->logs_sem), 0);
	return (1);
}

int	init_args(t_gen_var *gen_vars, t_philo *dinner)
{
	unsigned int	n_philos;
	int				i;

	n_philos = gen_vars->n_philo;
	i = -1;
	while ((unsigned int)++i < n_philos)
	{
		dinner[i].gen_vars = gen_vars;
		dinner[i].n_of_meals = 0;
		dinner[i].not_dead = 1;
		dinner[i].tid = i + 1;
	}
	return (1);
}
