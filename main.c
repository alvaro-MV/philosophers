/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:09:12 by alvmoral          #+#    #+#             */
/*   Updated: 2024/11/12 22:31:56by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *vargs)
{
	t_philo				*args;
	unsigned long long	timestamp;
	int					i;

	args = (t_philo *) vargs;
	pthread_mutex_lock(args->forks_mutex);
	i = 0;
	while (i++ < args->n_of_eats)
	{
		if (!compatible(args))
			manage_usleep(1);
		timestamp = get_actual_time();
		pthread_mutex_lock(&args->forks_mutex[args->tid]);
		take_fork_log(timestamp, args);
		args->forks_in_use[args->tid] = 1;
		pthread_mutex_lock(&args->forks_mutex[(args->tid + 1) % 5]);
		take_fork_log(timestamp, args);
		args->forks_in_use[(args->tid) % 5] = 1;
		eating__log(timestamp, args),
		usleep(1); //Número aleatorio tmstmp para sobar.
		sleeping_log(timestamp, args),
		usleep(1);
		thinking_log(timestamp, args);
		pthread_mutex_unlock(args->forks_mutex);
	}
}

/*
	Crear dos funciones, una para 
*/
int	main(void)
{
	pthread_t	forks[5];
	pthread_t	philosophers[5];
	t_philo		arg[5];
	int			i;
	int			*forks_in_use;

	i = 0;
	forks_in_use = (int *) ft_calloc(5, sizeof(int));
	while (i < 5)
	{
		if (pthread_mutex_init(forks[i], NULL));
		{
			write(1, "Mala creasion\n", 15);
			exit(-1);
		}
	}
	i = 0;
	while (i < 5)
	{
		if (pthread_mutex_init(&arg[i].forks_mutex, NULL))
		{
			write(1, "Mala creasion\n", 15);
			exit(-1);
		}
		arg[i].forks = forks;
		arg[i].tid = i;
		arg[i].forks_in_use = forks_in_use;
		if (pthread_create(philosophers[i++], NULL, philo_routine, &arg[i]));
		{
			write(1, "Mala creasion\n", 15);
			exit(-1);
		}
	}
	i = 0;
	while (i < 5)
		pthread_join(philosophers[i++], NULL);
	free(forks_in_use);
}
