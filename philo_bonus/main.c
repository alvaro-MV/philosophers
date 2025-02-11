/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:41:30 by alvmoral          #+#    #+#             */
/*   Updated: 2025/02/12 00:11:09 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_philos(t_philo *args)
{
	unsigned int	n_philo;
	unsigned int	i;

	i = 0;
	n_philo = args->gen_vars->n_philo;
	while (i < n_philo)
	{
		if (!args->not_dead)
		{
			args->gen_vars->philo_alive--;
			wait(NULL);
		}
		i++;
	}
}

void	close_all_sem(t_philo *arr_dinner)
{
	unsigned int	i;

	i = 0;
	close_sem(arr_dinner->gen_vars->logs_sem);
	close_sem(arr_dinner->last_meal_mutex);
	close_sem(arr_dinner->gen_vars->logs_sem);
	while (i < arr_dinner->gen_vars->n_philo)
	{
		close_sem(arr_dinner[i].last_meal_mutex);
		close_sem(arr_dinner->gen_vars->forks[i]);
		i++;	
	}
}

void	run_philos(t_gen_var *gen_vars, t_philo *arr_dinner)
{
	unsigned int	i;
	pid_t			ret;

	i = 0;
	gen_vars->init_time = 0;
	if (!init_args(gen_vars, arr_dinner))
		exit (-1);
	while (i < gen_vars->n_philo)
	{
		ret = fork();
		if (ret == -1)
		{
			write(2, "philo: error creating philosophers\n", 36);
			sem_wait(gen_vars->logs_sem);
			wait_philos(arr_dinner);
			close_all_sem(arr_dinner);
			p_free(gen_vars, arr_dinner);
			exit(-1);
		}
		if (ret == 0)
			philo_routine((void *) &arr_dinner[i]);
		i++;
	}
	gen_vars->init_time = get_actual_time();
	manager_routine(arr_dinner);
}

int	main(int argc, char **argv)
{
	t_gen_var	gen_vars;
	t_philo		*arr_dinner;

	if (argc < 5 || argc > 6)
	{
		write(1, "Format: ./philo <n_philo> <time_to_die> <time_to_eat>", 54);
		write(1, " <time_to_sleep> [n_times_must_eat]", 35);
		exit(1);
	}
	argv++;
	parse_input(&gen_vars, argv);
	p_new(&gen_vars, &arr_dinner);
	if (!init_protection_sem(&gen_vars))
		return (p_free(&gen_vars, arr_dinner), -1);
	if (!init_forks(&gen_vars))
		return (p_free(&gen_vars, arr_dinner), -1);
	run_philos(&gen_vars, arr_dinner);
	close_all_sem(arr_dinner);
	p_free(&gen_vars, arr_dinner);
}
