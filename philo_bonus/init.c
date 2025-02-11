/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:40:54 by alvmoral          #+#    #+#             */
/*   Updated: 2025/02/11 15:59:45 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_protection_sem(t_gen_var *gen_vars)
{
	if (sem_open("logs_sem", O_CREAT | O_RDWR, 1) == SEM_FAILED)
	{
		write(2, "philo: error initialization of logs sem.\n", 42);
		exit(-1);
	}
}

void	init_forks(t_gen_var *gen_vars)
{
	unsigned int	i;
	unsigned int	n_philos;

	i = 0;
	n_philos = gen_vars->n_philo;
	while (i < n_philos)
	{
		if (pthread_mutex_init(&gen_vars->forks[i], NULL))
		{
			write(2, "philo: error initialization of forks sem.\n", 43);
		}
		i++;
	}
}

void	init_args(t_gen_var *gen_vars, t_philo *dinner, pthread_t *philo)
{
	unsigned int	n_philos;
	unsigned int	i;

	n_philos = gen_vars->n_philo;
	i = 0;
	while (i < n_philos)
	{
		dinner[i].gen_vars = gen_vars;
		dinner[i].tid = i + 1;
		dinner[i].n_of_meals = 0;
		dinner[i].not_dead = 1;
		if (pthread_mutex_init(&dinner[i].last_meal_mutex, NULL))
		{
			write(2, "philo: error  creating mutex\n", 30);
			p_free(gen_vars, dinner, philo);
		}
		i++;
	}
}
