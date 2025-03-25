/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:39:52 by alvmoral          #+#    #+#             */
/*   Updated: 2025/03/25 14:50:22 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_log(t_philo *dinner, size_t action)
{
	uint64_t	time;

	time = get_actual_time();
	time = time - dinner->born_time;
	if (action)
		printf("\033[3;33m%lu %d has taken a fork\n", time, dinner->tid);
	else
		printf("\033[3;36m%lu %d has release a forks\n", time, dinner->tid);
}

void	eating_log(t_philo *dinner)
{
	uint64_t	time;

	time = get_actual_time();
	time = time - dinner->born_time;
	printf("\033[3;32m%lu %d is eating\n", time, dinner->tid);
}

void	sleeping_log(t_philo *dinner)
{
	uint64_t	time;

	time = get_actual_time();
	time = time - dinner->born_time;
	printf("\033[3;35m%lu %d is sleeping\n", time, dinner->tid);
}

void	thinking_log(t_philo *dinner)
{
	uint64_t	time;

	time = get_actual_time();
	time = time - dinner->born_time;
	printf("\033[3;34m%lu %d is thinking\n", time, dinner->tid);
}

void	died_log(t_philo *dinner)
{
	uint64_t	time;

	time = get_actual_time();
	time = time - dinner->born_time;
	printf("\033[3;31m%lu %d died\n\033[0m", time, dinner->tid);
}
