/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:41:17 by alvmoral          #+#    #+#             */
/*   Updated: 2025/02/14 18:35:51 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	p_new(t_gen_var *gen_vars, t_philo **dinner)
{
	unsigned int	n_philo;
	// sem_t			*forks;
	// sem_t			**forks;

	n_philo = gen_vars->n_philo;
	// forks = (sem_t **) malloc(n_philo * sizeof(sem_t *));
	// forks = (sem_t *) malloc(n_philo * sizeof(sem_t *));
	// if (!forks)
	// 	return ;
	// gen_vars->forks = forks;
	*dinner = (t_philo *) malloc(n_philo * sizeof(t_philo));
	if (!*dinner)
		ft_free_exit(gen_vars->forks);
}

void	close_sem(sem_t *sem, char *name)
{
	sem_close(sem);
	sem_unlink(name);
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