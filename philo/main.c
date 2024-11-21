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



void	wait_philos(t_philo *args, pthread_t *philosophers)
{
	unsigned int	n_philo;
	unsigned int	i;

	i = 0;
	n_philo = args->general_vars->n_philo;
	while (i < n_philo)
	{
		pthread_join(philosophers[i], NULL);
		i++;
	}
}

void	run_philos(t_gen_var *gen_vars, t_philo* args, pthread_t *philo)
{
	int			i;
	pthread_t	manager;

	i = 0;
	init_args(gen_vars, args, philo);
	while (i < gen_vars->n_philo)
	{
		ft_putnbr_fd(args[i].tid, 1);
		if (pthread_create(&philo[i], NULL, philo_routine, &args[i]))
		{
			write(2, "philo: error creating philosophers\n", 36);
			p_free(gen_vars, args, philo);
		}
		i++;
	}
	gen_vars->philo_ptrs = philo;
	if (pthread_create(&manager, NULL, manager_routine, args))
	{
		write(2, "philo: error creating philosophers\n", 36);
		p_free(gen_vars, args, philo);
	}
	wait_philos(args, philo);
	pthread_join(manager, NULL);
}

int	main(int argc, char **argv)
{
	t_gen_var	general_vars;
	t_philo		*arr_args;
	pthread_t	*philosophers;

	if (argc < 5 || argc > 6)
	{
		write(1, "Format: ./philo <n_philo> <time_to_die> <time_to_eat>", 54);
		write(1, " <time_to_sleep> [n_times_must_eat]", 35);
		exit(1);
	}
	argv++;
	parse_input(&general_vars, argv);
	p_alloc(&general_vars, &arr_args, &philosophers);	
	init_protection_mutexs(&general_vars);
	init_forks(&general_vars);
	run_philos(&general_vars, arr_args, philosophers);
	p_free(&general_vars, arr_args, philosophers);
}
