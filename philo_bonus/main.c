/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:41:30 by alvmoral          #+#    #+#             */
/*   Updated: 2025/02/14 11:39:52y alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_philos(t_philo *arr_dinner, int n_philo)
{
	int	j;	
	
	j = 0;
	while (j < n_philo)
		kill(arr_dinner[j++].pid, SIGKILL);
}

void	*wait_philos(void *vargs)
{
	unsigned int	n_philo;
	t_philo 		*arr_dinner;
	unsigned int	i;
	int				status;

	i = 0;
	arr_dinner = (t_philo *) vargs;
	n_philo = arr_dinner->gen_vars->n_philo;
	//testeo
	ft_printf("n philo: %d\n", n_philo);
	i = -1;
	while (++i  < n_philo)
		ft_printf("arr_pid %d :%d\n", i, arr_dinner[i].pid);
	i = 0;
	//testeo

	while (i < n_philo)
	{
		wait(&status);
		write(1, "Entras aquí\n", 14);
		ft_printf("status: %d\n", WEXITSTATUS(status)); //testeo
		if (WEXITSTATUS(status) == 9 || !WEXITSTATUS(status))
		{
			write(1, "Hijo de puta\n", 14);
			kill_philos(arr_dinner, n_philo);
			return (NULL);
		}
		i++;
	}
	return (NULL);
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
		free(sem_name);
		free(philo_id);
		i++;	
	}
}

void	run_philos(t_gen_var *gen_vars, t_philo *arr_dinner)
{
	unsigned int	i;
	pthread_t		orchestration;
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
			kill_philos(arr_dinner, i);
			close_all_sem(arr_dinner);
			free(arr_dinner);
			exit(-1);
		}
		arr_dinner[i].pid = ret;
		if (ret == 0)
			philo_routine((void *) &arr_dinner[i]);
		i++;
	}
	if (pthread_create(&orchestration, NULL, wait_philos, arr_dinner))
	{
		write(1, "Error creating manager thread.\n", 32);
		exit(-1);
	}
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
