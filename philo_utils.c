/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 21:08:19 by alvmoral          #+#    #+#             */
/*   Updated: 2024/11/16 01:50:47 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	compatible(t_philo *args)
{
	int	tid;

	tid = args->tid;
	if (!args->general_vars.forks_used[tid])
	{
		if (!args->general_vars.forks_used[(tid + 1) % 5])
			return (1);
	}
	else
		return (0);
}

unsigned long long	get_actual_time(void)
{
	struct timeval		tv;
	unsigned long long	timestamp;

	gettimeofday(&tv, NULL);
	timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000 - timestamp;
	return (timestamp);
}

unsigned long long	get_timestamp(unsigned long long timestamp)
{
	timestamp = get_actual_time() - timestamp;
	return (timestamp);
}