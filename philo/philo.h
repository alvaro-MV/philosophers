/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:09:15 by alvmoral          #+#    #+#             */
/*   Updated: 2024/11/19 13:29:29 by alvaro           ###   ########.fr       */
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
	pthread_mutex_t		*forks;
	unsigned int		n_philo;
	int					*forks_used;	
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned int		n_of_eats;
}						t_gen_var;

typedef struct	s_philo	
{
	t_gen_var			*general_vars;
	int					tid;
	pthread_t			thread_ptr;
	unsigned long long	time_last_meal;
	pthread_mutex_t		last_meal_mutex;
}						t_philo;

# define MAX_PHILOS 50
# define WAI_T 5

void				manage_usleep(__useconds_t	usenconds);
unsigned long long	get_actual_time(void);
unsigned long long	time_diff_usecs(unsigned long long start);
void				parse_input(t_gen_var *general_vars, char **argv);
void				p_alloc(t_gen_var *gen_vars, t_philo **args, pthread_t **philo);
void				p_free(t_gen_var *gen_vars, t_philo *args, pthread_t *philo);


void				init_protect_mutex(t_gen_var *general_vars);
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