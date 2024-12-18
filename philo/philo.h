/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:41:44 by alvmoral          #+#    #+#             */
/*   Updated: 2024/12/18 13:05:03 by alvaro           ###   ########.fr       */
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
	pthread_mutex_t		proc_mutex; //testeo
	pthread_mutex_t		death_mutex;
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
	int					run_4ever;
}						t_gen_var;

typedef struct s_philo	
{
	t_gen_var			*general_vars;
	int					tid;
	unsigned int		n_of_meals;
	unsigned long long	time_last_meal;
	pthread_mutex_t		last_meal_mutex;
	unsigned int		not_dead;
}						t_philo;

# define MAX_PHILOS 200
# define WAI_T 3

void				manage_usleep(__useconds_t	miliseconds);
unsigned long long	get_actual_time(void);
unsigned long long	time_diff_usecs(unsigned long long start);
void				parse_input(t_gen_var *general_vars, char **argv);
void				p_alloc(t_gen_var *gen_vars, t_philo **args, pthread_t **philo);
void				p_free(t_gen_var *gen_vars, t_philo *args, pthread_t *philo);
void				wait_philos(t_philo *args, pthread_t *philosophers);

void				init_protection_mutexs(t_gen_var *general_vars);
void				init_forks(t_gen_var *general_vars);
void				init_args(t_gen_var *gen_vars, t_philo *args, pthread_t *philo);


void				*philo_routine(void *vargs);
void				*manager_routine(void *args, pthread_t *philosophers);
int					compatible(t_philo *args);

void				take_forks(t_philo *args);
void				take_fork_log(t_philo *args, size_t action);
void				eating_log(t_philo *args);
void				sleeping_log(t_philo *args);
void				thinking_log(t_philo *args);
void				died_log(t_philo *args);

#endif