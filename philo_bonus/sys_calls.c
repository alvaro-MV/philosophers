/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_calls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:37:17 by alvmoral          #+#    #+#             */
/*   Updated: 2025/02/13 11:57:41 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	manage_usleep(sem_t *logs_sem, __useconds_t	miliseconds)
{
	uint64_t	start;

	(void) logs_sem;
	start = get_actual_time();
	while (get_actual_time() < start + miliseconds)
		usleep(9);
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
