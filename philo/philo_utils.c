/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 21:08:19 by alvmoral          #+#    #+#             */
/*   Updated: 2024/11/16 12:54:07by alvaro           ###   ########.fr       */
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

	gettimeofday(&tv, NULL);
	return (tv.tv_usec);
}

unsigned long long	time_diff_usecs(unsigned long long start)
{
	start = get_actual_time() - start;
	return (start);
}

void	check_philo_died(void)
{
	
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