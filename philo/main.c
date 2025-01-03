/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:41:30 by alvmoral          #+#    #+#             */
/*   Updated: 2025/01/02 11:44:36 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_philos(t_philo *args, pthread_t *philo)
{
	unsigned int	n_philo;
	unsigned int	i;
	// void			

	i = 0;
	n_philo = args->general_vars->n_philo;
	while (i < n_philo)
	{
		if (!args->not_dead)
		{
			args->general_vars->philo_alive--;
			pthread_join(philo[i], NULL);
		}
		i++;
	}
}

void	run_philos(t_gen_var *gen_vars, t_philo* args, pthread_t *philo)
{
	unsigned int	i;

	i = 0;
	gen_vars->init_time = 0;
	init_args(gen_vars, args, philo);
	while (i < gen_vars->n_philo)
	{
		if (pthread_create(&philo[i], NULL, philo_routine, &args[i]))
		{
			write(2, "philo: error creating philosophers\n", 36);
			// Si falla, hay que dar de baja el resto de hilos.
			p_free(gen_vars, args, philo);
		}
		i++;
	}
	gen_vars->philo_ptrs = philo;
	gen_vars->init_time = get_actual_time();
	manager_routine(args, philo);
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
	write(1, "Final", 6); //testeo
	p_free(&general_vars, arr_args, philosophers);
}
