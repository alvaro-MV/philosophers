/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:40:58 by alvmoral          #+#    #+#             */
/*   Updated: 2025/02/12 00:17:04 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_routine(t_philo *dinner)
{
	sem_t	*logs_sem;

	logs_sem = dinner->gen_vars->logs_sem;
	manage_usleep(logs_sem, dinner->gen_vars->time_to_sleep);
	sem_wait(dinner->gen_vars->logs_sem);
	if (!dinner->gen_vars->philo_alive)
		return ;
	sleeping_log(dinner);
	sem_post(dinner->gen_vars->logs_sem);
}

void	think_routine(t_philo *dinner)
{
	sem_wait(dinner->gen_vars->logs_sem);
	if (!dinner->gen_vars->philo_alive)
		return ;
	thinking_log(dinner);
	if (dinner->n_of_meals == dinner->gen_vars->max_meals)
	{
		dinner->gen_vars->philo_alive--;
		dinner->not_dead = 0;
	}
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
	if (!dinner->gen_vars->philo_alive)
		return ;
	if (dinner->tid % 2)
		drop_forks(gen, dinner, dinner->tid % gen->n_philo, dinner->tid - 1);
	else
		drop_forks(gen, dinner, dinner->tid - 1, dinner->tid % gen->n_philo);
	sem_post(gen->logs_sem);
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

	dinner = (t_philo *) vargs;
	i = 0;
	while (!dinner->gen_vars->init_time)
		;
	dinner->time_last_meal = dinner->gen_vars->init_time;
	if (dinner->tid % 2)
		usleep(450);
	while (1)
	{
		if (!check_running(dinner, &i))
			return (NULL);
		take_forks_dispatcher(dinner);
		eat_routine(dinner);
		sleep_routine(dinner);
		think_routine(dinner);
		if (!dinner->gen_vars->philo_alive)
			break ;
	}
	return (NULL);
}
