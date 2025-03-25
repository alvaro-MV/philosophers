/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:40:54 by alvmoral          #+#    #+#             */
/*   Updated: 2025/03/25 15:13:11 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_protection_mutexs(t_gen_var *gen_vars)
{
	if (pthread_mutex_init(&gen_vars->logs_mutex, NULL))
	{
		write(2, "philo: error initialization of protection mutex\n", 49);
		return (0);
	}
	if (pthread_mutex_init(&gen_vars->death_mutex, NULL))
	{
		write(2, "philo: error initialization of protection mutex\n", 49);
		return (0);
	}
	return (1);
}

int	init_forks(t_gen_var *gen_vars)
{
	unsigned int	i;
	unsigned int	n_philos;

	i = 0;
	n_philos = gen_vars->n_philo;
	while (i < n_philos)
	{
		if (pthread_mutex_init(&gen_vars->forks[i], NULL))
		{
			write(2, "philo: error initialization of forks mutex\n", 44);
			return (0);
		}
		i++;
	}
	return (1);
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
		dinner[i].th_finish = 0;
		if (pthread_mutex_init(&dinner[i].last_meal_mutex, NULL))
		{
			write(2, "philo: error  creating mutex\n", 30);
			p_free(gen_vars, dinner, philo);
		}
		i++;
	}
}

t_philo	*init_philo_routine(void *vargs, unsigned int *i)
{
	t_philo			*dinner;

	dinner = (t_philo *) vargs;
	*i = 0;
	pthread_mutex_lock(&dinner->gen_vars->logs_mutex);
	dinner->born_time = get_actual_time();
	dinner->time_last_meal = get_actual_time();
	pthread_mutex_unlock(&dinner->gen_vars->logs_mutex);
	if (dinner->tid % 2)
		usleep(450);
	manage_usleep(5);
	return (dinner);
}
