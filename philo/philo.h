/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:09:15 by alvmoral          #+#    #+#             */
/*   Updated: 2024/11/18 10:06:48 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <limits.h>
#include "libft/libft.h"

typedef struct s_general_vars
{
	pthread_mutex_t		*proc_mutex;
	pthread_mutex_t 	*forks;
	unsigned int		n_philo;
	int					*forks_used;	
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned int		n_of_eats;
}						t_general_vars;

typedef struct s_philo	
{
	t_general_vars	general_vars;
	int				tid;
}					t_philo;

# define MAX_PHILOS 50
# define WAI_T 5

void				manage_usleep(__useconds_t	usenconds);
unsigned long long	get_actual_time(void);
unsigned long long	time_diff_usecs(unsigned long long start);

void				*philo_routine(void *vargs);

void				take_fork_log(unsigned long long timestamp, t_philo *args);
void				eating_log(unsigned long long timestamp, t_philo *args);
void				sleeping_log(unsigned long long timestamp, t_philo *args);
void				thinking_log(unsigned long long timestamp, t_philo *args);
void				died_log(unsigned long long timestamp, t_philo *args);

#endif