/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:40:54 by alvmoral          #+#    #+#             */
/*   Updated: 2025/02/12 13:28:03 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_protection_sem(t_gen_var *gen_vars)
{
	sem_unlink("/logs_sem");
	gen_vars->logs_sem = sem_open("/logs_sem", O_CREAT, S_IRUSR, 1);
	if (gen_vars->logs_sem == SEM_FAILED)
	{
		perror("que ostias pasa");
		write(2, "philo: error initialization of logs sem.\n", 42);
		return (0);
	}
	return (1);
}

static int	close_error_forks(sem_t **forks, int i_fail)
{
	int	i;

	i = 0;
	write(2, "philo: error initialization of forks sem.\n", 43);
	while (i < i_fail)
	{
		sem_close(forks[i]);
		i++;
	}
	return (0);
}

int	init_forks(t_gen_var *gen_vars)
{
	unsigned int	i;
	unsigned int	n_philos;
	char			*fork_id;
	char			*sem_fork_name;

	i = 0;
	n_philos = gen_vars->n_philo;
	while (i < n_philos)
	{
		fork_id = ft_itoa(i);
		if (!fork_id)
			return (0);
		sem_fork_name = ft_strjoin("/fork_", fork_id);
		if (!sem_fork_name)
			return (free(fork_id), 0);
		free(fork_id);
		sem_unlink(sem_fork_name);
		gen_vars->forks[i] = sem_open(sem_fork_name, O_CREAT, S_IRUSR, 1);
		free(sem_fork_name);
		if (gen_vars->forks[i] == SEM_FAILED)
			return (close_error_forks(gen_vars->forks, i),
				sem_close(gen_vars->logs_sem), 0);
		i++;
	}
	return (1);
}

static int	close_error_meal(t_gen_var *gen_vars, t_philo *dinner, int i_fail)
{
	int	i;

	i = 0;
	write(2, "philo: error  creating semphore\n", 33);
	while (i < i_fail)
	{
		sem_close(dinner[i].last_meal_mutex);
		i++;
	}
	sem_close(gen_vars->logs_sem);
	close_error_forks(gen_vars->forks, gen_vars->n_philo);
	p_free(gen_vars, dinner);
	return (0);
}

int	init_args(t_gen_var *gen_vars, t_philo *dinner)
{
	unsigned int	n_philos;
	int				i;
	char			*philo_id;
	char			*sem_name;

	n_philos = gen_vars->n_philo;
	i = -1;
	while ((unsigned int) ++i < n_philos)
	{
		dinner[i].gen_vars = gen_vars;
		dinner[i].tid = i + 1;
		dinner[i].n_of_meals = 0;
		dinner[i].not_dead = 1;
		philo_id = ft_itoa(i);
		if (!philo_id)
			return (0);
		sem_name = ft_strjoin("/last_meal_", philo_id);
		free(philo_id);
		if (!sem_name)
			return (0);
		sem_unlink(sem_name);
		dinner[i].last_meal_mutex = sem_open(sem_name, O_CREAT, S_IRWXU, 1);
		free(sem_name);
		if (dinner[i].last_meal_mutex == SEM_FAILED)
			return (close_error_meal(gen_vars, dinner, i));
	}
	return (1);
}
