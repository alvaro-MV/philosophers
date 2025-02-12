/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_calls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:37:17 by alvmoral          #+#    #+#             */
/*   Updated: 2025/02/12 19:02:47 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	manage_usleep(sem_t *logs_sem, __useconds_t	miliseconds)
{
	uint64_t	start;

	(void) logs_sem;
	start = get_actual_time();
	write(1, "EL seño de la noche\n", 22);
	while (get_actual_time() < start + (uint64_t) miliseconds);
	{
		usleep(9);
		// if (usleep(9) == -1)
		// 	sem_wait(logs_sem);
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
