/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:09:15 by alvmoral          #+#    #+#             */
/*   Updated: 2024/11/15 00:51:48 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

typedef struct s_philo	
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_of_eats;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	*forks;
	int				tid;
	int				*forks_in_use;
}					t_philo;

void    			ft_putstr_fd(char *s, int fd);
void    			ft_putnbr_fd(int n, int fd);
void				manage_usleep(__useconds_t	usenconds);
unsigned long long	get_actual_time(void);
unsigned long long	get_timestamp(unsigned long long timestamp);

void	take_fork_log(unsigned long long timestamp, t_philo *args);
void	eating_log(unsigned long long timestamp, t_philo *args);
void	sleeping_log(unsigned long long timestamp, t_philo *args);
void	thinking_log(unsigned long long timestamp, t_philo *args);
void	died_log(unsigned long long timestamp, t_philo *args);

#endif