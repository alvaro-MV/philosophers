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
	if (pthread_mutex_init(&general_vars->proc_mutex, NULL))
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
		if (!pthread_mutex_init(&general_vars->forks[i], NULL))
		{
			write(2, "Mala creasion\n", 15);
			ft_free_exit(general_vars->forks_used);
		}
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
	pthread_t	manager;

	i = 0;
	while (i < gen_vars->n_philo)
	{
		args[i].general_vars = *gen_vars;	
		args[i].tid = i;
		args[i].thread_ptr = philo[i];
		if (pthread_create(&philo[i++], NULL, philo_routine, &args[i]));
		{
			write(2, "Mala creasion\n", 15);
			p_free(gen_vars, args, philo);
		}
	}
	if (pthread_create(&manager, NULL, manager_routine, args))
	{
		write(2, "Mala creasion\n", 15);
		p_free(gen_vars, args, philo);
	}
	wait_philos(philo);
	pthread_join(manager, NULL);
}

int	main(int argc, char **argv)
{
	t_general_vars	general_vars;
	t_philo			*arr_args;
	pthread_t		*philosophers;

	if (argc < 5 || argc > 6)
	{
		write(1, "Format: ./philo <n_philo> <time_to_die> <time_to_eat>", 54);
		write(1, " <time_to_sleep> [n_times_must_eat]", 35);
		exit(1);
	}
	argv++;
	parse_input(&general_vars, argv);
	p_alloc(&general_vars, arr_args, philosophers);	
	init_protect_mutex(&general_vars);
	init_forks(&general_vars);
	run_philos(&general_vars, arr_args, philosophers);
	p_free(&general_vars, arr_args, philosophers);
}
