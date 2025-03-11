/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:41:44 by alvmoral          #+#    #+#             */
/*   Updated: 2025/03/11 12:12:19 by alvaro           ###   ########.fr       */
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
# include "utils/utils.h"

typedef struct s_general_vars
{
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	logs_mutex;
	pthread_mutex_t	*forks;
	pthread_t		*philo_ptrs;
	unsigned int	n_philo;
	int				*forks_used;	
	uint64_t		init_time;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	unsigned int	max_meals;
	unsigned int	philo_alive;
	int				run_4ever;
}					t_gen_var;

typedef struct s_philo
{
	t_gen_var		*gen_vars;
	unsigned int	tid;
	unsigned int	n_of_meals;
	uint64_t		time_last_meal;
	uint64_t		born_time;
	pthread_mutex_t	last_meal_mutex;
	unsigned int	not_dead;
	unsigned int	th_finish;
}					t_philo;

# define MAX_PHILOS 200
# define WAI_T 13

// ************Utils*****************

void		manage_usleep(__useconds_t miliseconds);
uint64_t	get_actual_time(void);
uint64_t	time_diff_usecs(uint64_t start);
void		parse_input(t_gen_var *gen_vars, char **argv);
void		p_new(t_gen_var *gen_vars, t_philo **args, pthread_t **philo);
void		p_free(t_gen_var *gen_vars, t_philo *args, pthread_t *philo);
void		wait_philos(t_philo *args, pthread_t *philosophers);

/* 	*************Initialization******* */

int			init_protection_mutexs(t_gen_var *general_vars);
int			init_forks(t_gen_var *gen_vars);
void		init_args(t_gen_var *gen_vars, t_philo *args, pthread_t *philo);
t_philo		*init_philo_routine(void *vargs, unsigned int *i);

/* ***************Routines************* */

void		*philo_routine(void *vargs);
void		*manager_routine(void *vargs, pthread_t *philo);
int			compatible(t_philo *args);

/* ***************Forks***************** */

int			take_forks_dispatcher(t_philo *dinner);
int			take_forks(t_gen_var *gen, t_philo *args, int f1, int f2);
void		drop_forks(t_gen_var *gen, t_philo *args, int f1, int f2);

/* ***************Logs****************** */
void		fork_log(t_philo *dinner, size_t action);
void		eating_log(t_philo *dinner);
void		sleeping_log(t_philo *dinner);
void		thinking_log(t_philo *dinner);
void		died_log(t_philo *dinner);

#endif