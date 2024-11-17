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

int	main(int argc, char **argv)
{
	t_general_vars	general_vars;

	if (argc < 5 || argc > 6)
	{
		write(1, "Format: ./philo <n_philo> <time_to_die> <time_to_eat>", 54);
		write(1, " <time_to_sleep> [n_times_must_eat]", 35);
		exit(1);
	}
	argv++;
	init_protect_mutex(&general_vars);
	init_forks(&general_vars);
	run_philos(&general_vars);
	free_forks(&general_vars);
}
