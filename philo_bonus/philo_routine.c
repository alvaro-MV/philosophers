/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:40:58 by alvmoral          #+#    #+#             */
/*   Updated: 2025/03/03 18:03:42 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_routine(t_philo *dinner)
{
	sem_t	*logs_sem;

	logs_sem = dinner->gen_vars->logs_sem;
	manage_usleep(logs_sem, dinner->gen_vars->time_to_sleep);
	sem_wait(dinner->gen_vars->logs_sem);
	sleeping_log(dinner);
	sem_post(dinner->gen_vars->logs_sem);
}

void	think_routine(t_philo *dinner)
{
	sem_wait(dinner->gen_vars->logs_sem);
	thinking_log(dinner);
	sem_post(dinner->gen_vars->logs_sem);
}

void	eat_routine(t_philo *dinner)
{
	t_gen_var	*gen;
	sem_t		*logs_sem;

	logs_sem = dinner->gen_vars->logs_sem;
	gen = dinner->gen_vars;
	sem_wait(gen->logs_sem);
	eating_log(dinner);
	dinner->time_last_meal = get_actual_time();
	dinner->n_of_meals++;
	sem_post(gen->logs_sem);
	manage_usleep(logs_sem, gen->time_to_eat);
	sem_wait(gen->logs_sem);
	if (dinner->tid % 2)
		drop_forks(gen, dinner, dinner->tid % gen->n_philo, dinner->tid - 1);
	else
		drop_forks(gen, dinner, dinner->tid - 1, dinner->tid % gen->n_philo);
	sem_post(gen->logs_sem);
}

static int	check_running(t_philo *dinner, unsigned int *i)
{
	if (!dinner->not_dead)
	{
		pthread_join(dinner->manager, NULL);
		exit(PHILO_DIED);
	}
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
		{
			dinner->not_dead = 0;
			return (0);
		}
	}
}

void	philo_routine(void *vargs)
{
	t_philo			*dinner;
	unsigned int	i;

	dinner = (t_philo *) vargs;
	i = 0;
	if (pthread_create(&dinner->manager, NULL, manager_routine, dinner))
	{
		write(1, "Error creating manager thread.\n", 32);
		exit(-1);
	}
	sem_wait(dinner->gen_vars->last_meal_mutex);
	dinner->time_last_meal = dinner->gen_vars->init_time;
	sem_post(dinner->gen_vars->last_meal_mutex);
	if (dinner->tid % 2)
		usleep(25000);
	while (check_running(dinner, &i))
	{
		take_forks_dispatcher(dinner);
		eat_routine(dinner);
		sleep_routine(dinner);
		think_routine(dinner);
	}
	pthread_join(dinner->manager, NULL);
	exit(PHILO_END_EATING);
}
