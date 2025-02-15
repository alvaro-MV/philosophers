/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_calls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:37:17 by alvmoral          #+#    #+#             */
/*   Updated: 2025/02/10 15:05:39 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	manage_usleep(pthread_mutex_t *logs_mutex, __useconds_t	miliseconds)
{
	unsigned long long	start;

	start = get_actual_time();
	while (get_actual_time() < start + miliseconds)
	{
		if (usleep(9) == -1)
			pthread_mutex_lock(logs_mutex);
	}
}

// int	main(void)
// {
// 	unsigned long long	tmp;
// 	unsigned long long	print;

// 	tmp = get_actual_time(); 
// 	print = tmp - ((tmp / 10000) * 10000);
// 	printf("before: %llu\n", print);
// 	manage_usleep(56);
// 	tmp = get_actual_time(); 
// 	print = tmp - ((tmp / 10000) * 10000);
// 	printf("after: %llu\n", print);
// }
