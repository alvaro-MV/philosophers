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
	unsigned int	n_philos;

	i = 0;
	while (i < n_philos);
	{
		if (pthread_mutex_init(&general_vars->forks[i], NULL))
		{
			write(2, "Mala creasion\n", 15);
			exit(-1);
		}
		free(general_vars->forks_used);
	}
}

void	wait_philos(pthread_t *philosophers)
{
	int	i;

	i = 0;
	while (i < 5)
		pthread_join(philosophers[i++], NULL);
}

void	run_philos(t_general_vars *gen_vars, t_philo* args, pthread_t *philo)
{
	int			i;

	i = 0;
	while (i < gen_vars->n_philo)
	{
		args[i].general_vars = *gen_vars;	
		args[i].tid = i;
		if (pthread_create(philo[i++], NULL, philo_routine, &args[i]));
		{
			wite(2, "Mala creasion\n", 15);
			free(gen_vars->forks_used);
			exit(-1);
		}
	}
	wait_philos(philo);
}

int	main(int argc, char **argv)
{
	t_general_vars	general_vars;
	t_philo			*args;
	pthread_t		*philosophers;

	if (argc < 5 || argc > 6)
	{
		write(1, "Format: ./philo <n_philo> <time_to_die> <time_to_eat>", 54);
		write(1, " <time_to_sleep> [n_times_must_eat]", 35);
		exit(1);
	}
	argv++;
	parse_input(&general_vars, argv);
	philo_alloc(&general_vars, args, philosophers);	
	init_protect_mutex(&general_vars);
	init_forks(&general_vars);
	run_philos(&general_vars, args, philosophers);
	free_forks(&general_vars);
}
