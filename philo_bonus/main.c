/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:41:30 by alvmoral          #+#    #+#             */
/*   Updated: 2025/02/13 19:31:51 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_philos(t_philo *arr_dinner)
{
	unsigned int	n_philo;
	unsigned int	i;
	unsigned int	j;
	int				status;

	i = 0;
	j = 0;
	n_philo = arr_dinner->gen_vars->n_philo;
	while (i < n_philo)
	{
		arr_dinner->gen_vars->philo_alive--;
		waitpid(arr_dinner[i].pid, &status, 0);
		if (status == 9)
		{
			write(1, "Pero que está pasando\n", 24);
			while (j < n_philo)
				kill(arr_dinner[j++].pid, SIGKILL);
		}
		i++;
	}
}

void	close_all_sem(t_philo *arr_dinner)
{
	unsigned int	i;
	char			*sem_name;
	char			*philo_id;

	i = 0;
	close_sem(arr_dinner->gen_vars->forks, "/forks");
	close_sem(arr_dinner->gen_vars->logs_sem, "/logs_sem");
	while (i < arr_dinner->gen_vars->n_philo)
	{
		philo_id = ft_itoa(i);
		sem_name = ft_strjoin("/last_meal_", philo_id);
		close_sem(arr_dinner[i].last_meal_mutex, sem_name);
		free(sem_name);
		free(philo_id);
		i++;	
	}
}

void	run_philos(t_gen_var *gen_vars, t_philo *arr_dinner)
{
	unsigned int	i;
	pid_t			ret;

	i = 0;
	if (!init_args(gen_vars, arr_dinner))
		exit (-1);
	gen_vars->init_time = get_actual_time();
	while (i < gen_vars->n_philo)
	{
		arr_dinner[i].time_last_meal = gen_vars->init_time;
		ret = fork();
		if (ret == -1)
		{
			write(2, "philo: error creating philosophers\n", 36);
			sem_wait(gen_vars->logs_sem);
			wait_philos(arr_dinner);
			close_all_sem(arr_dinner);
			free(arr_dinner);
			exit(-1);
		}
		arr_dinner[i].pid = ret;
		if (ret == 0)
			philo_routine((void *) &arr_dinner[i]);
		i++;
	}
	wait_philos(arr_dinner);
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
		return (free(arr_dinner), -1);
	if (!init_forks(&gen_vars))
		return (free(arr_dinner), -1);
	run_philos(&gen_vars, arr_dinner);
	close_all_sem(arr_dinner);
	free(arr_dinner);
}
