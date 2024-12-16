/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:41:17 by alvmoral          #+#    #+#             */
/*   Updated: 2024/12/12 22:47:18 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	compatible(t_philo *args)
{
	t_gen_var *gen;

	gen = args->general_vars;
	if (!gen->forks_used[args->tid])
	{
		if (!gen->forks_used[(args->tid + 1) % gen->n_philo])
			return (1);
	}
	return (0);
}

unsigned long long	get_actual_time(void)
{
	struct timeval		tv;
	unsigned long long	timestamp;

	gettimeofday(&tv, NULL);
	timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (timestamp);
}

unsigned long long	time_diff_usecs(unsigned long long start)
{
	start = get_actual_time() - start;
	return (start);
}

void	p_alloc(t_gen_var *gen_vars, t_philo **args, pthread_t **philo)
{
	unsigned int	n_philo;
	pthread_mutex_t	*forks;

	n_philo = gen_vars->n_philo;
	gen_vars->forks_used = (int *) ft_calloc(n_philo, sizeof(int));
	forks = (pthread_mutex_t *) malloc(n_philo * sizeof(pthread_mutex_t));
	if (!forks)
		ft_free_exit(gen_vars->forks_used);
	gen_vars->forks = forks;
	*args = (t_philo *) malloc(n_philo * sizeof(t_philo));
	if (!*args)
	{
		free(gen_vars->forks_used);
		ft_free_exit(gen_vars->forks);
	}
	*philo = (pthread_t *) malloc(n_philo * sizeof(pthread_t));
	if (!*philo)
	{
		free(gen_vars->forks_used);
		free(gen_vars->forks);
		ft_free_exit(*args);
	}
}

void	p_free(t_gen_var *gen_vars, t_philo *args, pthread_t *philo)
{
	free(gen_vars->forks_used);
	free(gen_vars->forks);
	free(args);
	ft_free_exit(philo);
}

// int	main(void)
// {
// 	unsigned long long	timestamp;
// 	unsigned long long	zero_tmstmp;
// 	struct timeval		tv;
// 	int	i = 0;

// 	gettimeofday(&tv, NULL);
// 	zero_tmstmp = tv.tv_usec;
// 	while (i < 7)
// 	{
// 		gettimeofday(&tv, NULL);
// 		timestamp = tv.tv_usec - zero_tmstmp;
// 		printf("Paco Javier: %llu\n", timestamp);
// 		i++;
// 	}
// 	return (0);
// }