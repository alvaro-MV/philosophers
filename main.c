/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:09:12 by alvmoral          #+#    #+#             */
/*   Updated: 2024/11/15 13:39:29by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *vargs)
{
	t_philo				*args;
	unsigned long long	timestamp;
	int					i;

	args = (t_philo *) vargs;
	pthread_mutex_lock(args->general_vars.proc_mutex);
	i = 0;
	while (i++ < args->general_vars.n_of_eats)
	{
		if (!compatible(args))
			manage_usleep(1);
		timestamp = get_actual_time();
		pthread_mutex_lock(&args->general_vars.proc_mutex[args->tid]);
		take_fork_log(timestamp, args);
		args->general_vars.forks_used[args->tid] = 1;
		pthread_mutex_lock(&args->general_vars.proc_mutex[(args->tid + 1) % 5]);
		take_fork_log(timestamp, args);
		args->general_vars.forks_used[(args->tid) % 5] = 1;
		eating__log(timestamp, args),
		usleep(1); //Número aleatorio tmstmp para sobar.
		sleeping_log(timestamp, args),
		usleep(1);
		thinking_log(timestamp, args);
		pthread_mutex_unlock(args->general_vars.proc_mutex);
	}
}

void	init_protect_mutex(t_general_vars *general_vars)
{
	if (pthread_mutex_init(general_vars->proc_mutex, NULL))
	{
		write(2, "Mala creasion\n", 15);
		exit(-1);
	}
}

void	init_forks(t_general_vars *general_vars)
{
	int	i;
	pthread_t	forks[5];

	i = 0;
	general_vars->forks_used = (int *) ft_calloc(5, sizeof(int));
	if (!general_vars->forks_used)
		exit (-1);
	free(general_vars->forks_used);
	while (i < 5)
	{
		if (pthread_mutex_init(forks[i], NULL));
		{
			write(2, "Mala creasion\n", 15);
			exit(-1);
		}
		free(general_vars->forks_used);
	}
	general_vars->forks = forks;
}

void	wait_philos(pthread_t *philosophers)
{
	int	i;

	i = 0;
	while (i < 5)
		pthread_join(philosophers[i++], NULL);
}

void	run_philos(t_general_vars *general_vars)
{
	int			i;
	t_philo		arg[5];
	pthread_t	philosophers[5];

	i = 0;
	while (i < 5)
	{
		arg[i].general_vars = *general_vars;	
		arg[i].tid = i;
		if (pthread_create(philosophers[i++], NULL, philo_routine, &arg[i]));
		{
			wite(2, "Mala creasion\n", 15);
			free(general_vars->forks_used);
			exit(-1);
		}
	}
	wait_philos(philosophers);
}

int	main(void)
{
	t_general_vars	general_vars;

	// Parseo necesario: Nuevos campos dentro de la estructura: los philos y toda la hostia.
	init_protect_mutex(&general_vars);
	init_forks(&general_vars);
	run_philos(&general_vars);
	free_forks(&general_vars);
}
