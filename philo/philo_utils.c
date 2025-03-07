/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:41:17 by alvmoral          #+#    #+#             */
/*   Updated: 2025/03/07 13:35:57 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	compatible(t_philo *dinner)
{
	t_gen_var	*gen;

	gen = dinner->gen_vars;
	if (!gen->forks_used[dinner->tid - 1])
	{
		if (!gen->forks_used[(dinner->tid) % gen->n_philo])
			return (1);
	}
	return (0);
}

uint64_t	get_actual_time(void)
{
	struct timeval	tv;
	uint64_t		timestamp;

	gettimeofday(&tv, NULL);
	timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (timestamp);
}

uint64_t	time_diff_usecs(uint64_t start)
{
	uint64_t	actual;
	uint64_t	returned;

	actual = get_actual_time();
	returned = actual - start;
	return (returned);
}

void	p_new(t_gen_var *gen_vars, t_philo **dinner, pthread_t **philo)
{
	unsigned int	n_philo;
	pthread_mutex_t	*forks;

	n_philo = gen_vars->n_philo;
	gen_vars->forks_used = (int *) ft_calloc(n_philo, sizeof(int));
	forks = (pthread_mutex_t *) malloc(n_philo * sizeof(pthread_mutex_t));
	if (!forks)
		ft_free_exit(gen_vars->forks_used);
	gen_vars->forks = forks;
	*dinner = (t_philo *) malloc(n_philo * sizeof(t_philo));
	if (!*dinner)
	{
		free(gen_vars->forks_used);
		ft_free_exit(gen_vars->forks);
	}
	*philo = (pthread_t *) malloc(n_philo * sizeof(pthread_t));
	if (!*philo)
	{
		free(gen_vars->forks_used);
		free(gen_vars->forks);
		ft_free_exit(*dinner);
	}
}

void	p_free(t_gen_var *gen_vars, t_philo *dinner, pthread_t *philo)
{
	while (dinner->gen_vars->philo_alive)
		;
	free(gen_vars->forks_used);
	free(gen_vars->forks);
	free(dinner);
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