/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:41:30 by alvmoral          #+#    #+#             */
/*   Updated: 2025/03/07 18:43:08 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_philos(t_philo *args, pthread_t *philo)
{
	unsigned int	n_philo;
	unsigned int	i;

	i = 0;
	n_philo = args->gen_vars->n_philo;
	while (i < n_philo && args->not_dead)
	{
		args->gen_vars->philo_alive--;
		pthread_detach(philo[i]);
		i++;
	}
	// pthread_mutex_unlock(&args->gen_vars->logs_mutex);
}

void	run_philos(t_gen_var *gen_vars, t_philo *dinner, pthread_t *philo)
{
	unsigned int	i;

	i = 0;
	init_args(gen_vars, dinner, philo);
	gen_vars->philo_ptrs = philo;
	gen_vars->init_time = get_actual_time();
	while (i < gen_vars->n_philo)
	{
		if (pthread_create(&philo[i], NULL, philo_routine, &dinner[i]))
		{
			write(2, "philo: error creating philosophers\n", 36);
			pthread_mutex_lock(&gen_vars->logs_mutex);
			p_free(gen_vars, dinner, philo);
		}
		i++;
	}
	manager_routine(dinner, philo);
}

int	main(int argc, char **argv)
{
	t_gen_var	gen_vars;
	t_philo		*arr_dinner;
	pthread_t	*philosophers;

	if (argc < 5 || argc > 6)
	{
		write(1, "Format: ./philo <n_philo> <time_to_die> <time_to_eat>", 54);
		write(1, " <time_to_sleep> [n_times_must_eat]", 35);
		exit(1);
	}
	argv++;
	parse_input(&gen_vars, argv);
	p_new(&gen_vars, &arr_dinner, &philosophers);
	if (!init_protection_mutexs(&gen_vars))
		return (p_free(&gen_vars, arr_dinner, philosophers), -1);
	if (!init_forks(&gen_vars))
		return (p_free(&gen_vars, arr_dinner, philosophers), -1);
	run_philos(&gen_vars, arr_dinner, philosophers);
	p_free(&gen_vars, arr_dinner, philosophers);
}
