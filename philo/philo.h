/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:09:15 by alvmoral          #+#    #+#             */
/*   Updated: 2024/11/25 14:08:45 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/time.h>
# include <time.h>
# include <limits.h>
# include "libft/libft.h"

typedef struct s_general_vars
{
	pthread_mutex_t		proc_mutex;
	pthread_mutex_t		logs_mutex;
	pthread_mutex_t		*forks;
	pthread_t			*philo_ptrs;
	unsigned int		n_philo;
	int					*forks_used;	
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned int		max_meals;
	unsigned int		philo_alive;
}						t_gen_var;

typedef struct	s_philo	
{
	t_gen_var			*general_vars;
	int					tid;
	int					n_of_meals;
	unsigned long long	time_last_meal;
	pthread_mutex_t		last_meal_mutex;
}						t_philo;

# define MAX_PHILOS 50
# define WAI_T 100

void				manage_usleep(__useconds_t	usenconds);
unsigned long long	get_actual_time(void);
unsigned long long	time_diff_usecs(unsigned long long start);
void				parse_input(t_gen_var *general_vars, char **argv);
void				p_alloc(t_gen_var *gen_vars, t_philo **args, pthread_t **philo);
void				p_free(t_gen_var *gen_vars, t_philo *args, pthread_t *philo);


void				init_protection_mutexs(t_gen_var *general_vars);
void				init_forks(t_gen_var *general_vars);
void				init_args(t_gen_var *gen_vars, t_philo *args, pthread_t *philo);


void				*philo_routine(void *vargs);
void				*manager_routine(void *args);
int					compatible(t_philo *args);

void				take_forks(t_philo *args);
void				take_fork_log(t_philo *args);
void				eating_log(t_philo *args);
void				sleeping_log(t_philo *args);
void				thinking_log(t_philo *args);
void				died_log(t_philo *args);

#endif