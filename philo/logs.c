/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:39:52 by alvmoral          #+#    #+#             */
/*   Updated: 2025/03/19 17:14:58 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_log(t_philo *dinner, size_t action)
{
	uint64_t	time;

	time = get_actual_time();
	time = time - dinner->born_time;
	if (action)
		ft_printf("\033[3;33m%l %d has taken a fork\n", time, dinner->tid);
	else
		ft_printf("\033[3;36m%l %d has release a forks\n", time, dinner->tid);
}

void	eating_log(t_philo *dinner)
{
	uint64_t	time;

	time = get_actual_time();
	time = time - dinner->time_last_meal;
	printf("\033[3;32m%lu %d is eating\n", time, dinner->tid);
}

void	sleeping_log(t_philo *dinner)
{
	uint64_t	time;

	time = get_actual_time();
	time = time - dinner->born_time;
	ft_printf("\033[3;35m%l %d is sleeping\n", time, dinner->tid);
}

void	thinking_log(t_philo *dinner)
{
	uint64_t	time;

	time = get_actual_time();
	time = time - dinner->born_time;
	ft_printf("\033[3;34m%l %d is thinking\n", time, dinner->tid);
}

void	died_log(t_philo *dinner)
{
	uint64_t	time;

	time = get_actual_time();
	time = time - dinner->born_time;
	ft_printf("\033[3;31m%l %d died\n\033[0m", time, dinner->tid);
}
