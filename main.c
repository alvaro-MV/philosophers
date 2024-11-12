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
	t_philo	*args;

	args = (t_philo *) vargs;
	pthread_mutex_lock(args->forks_mutex);
	if (!compatible())
		manage_usleep(1);
	pthread_mutex_unlock(args->forks_mutex);
	
}

int	main(void)
{
	pthread_t		forks[5];
	pthread_t		philosophers[5];
	t_philo			*arg;
	int				i;


	i = 0;
	while (i < 5)
	{
		if (pthread_mutex_init(forks[i], NULL));
		{
			write(1, "Mala creasion\n", 15);
			exit(-1);
		}
	}
	i = 0;
	pthread_mutex_init(&arg->forks_mutex, NULL);
	arg->forks = &forks;
	i = 0;
	while (i < 5)
	{
		if (pthread_create(philosophers[i++], NULL, philo_routine, arg));
		{
			write(1, "Mala creasion\n", 15);
			exit(-1);
		}
	}
	i = 0;
	while (i < 5)
		pthread_join(forks[i], NULL);
}
