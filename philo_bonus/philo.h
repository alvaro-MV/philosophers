/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:41:44 by alvmoral          #+#    #+#             */
/*   Updated: 2025/02/11 12:51:28 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <unistd.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/time.h>
# include <time.h>
# include <limits.h>
# include "libft/libft.h"

typedef struct s_general_vars
{
	sem_t			logs_mutex;
	sem_t			*forks;
	pthread_t		*philo_ptrs;
	unsigned int	n_philo;
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
	sem_t			last_meal_mutex;
	unsigned int	not_dead;
}					t_philo;

# define MAX_PHILOS 200
# define WAI_T 13

// ************Utils*****************

void		manage_usleep(pthread_mutex_t *mutex, __useconds_t miliseconds);
uint64_t	get_actual_time(void);
uint64_t	time_diff_usecs(uint64_t start);
void		parse_input(t_gen_var *gen_vars, char **argv);
void		p_new(t_gen_var *gen_vars, t_philo **dinner);
void		p_free(t_gen_var *gen_vars, t_philo *dinner);
void		wait_philos(t_philo *args, pthread_t *philosophers);

/* 	*************Initialization******* */

void		init_protection_sem(t_gen_var *general_vars);
void		init_forks(t_gen_var *gen_vars);
void		init_args(t_gen_var *gen_vars, t_philo *args, pthread_t *philo);

/* ***************Routines************* */

void		*philo_routine(void *vargs);
void		*manager_routine(void *vargs, pthread_t *philo);
int			compatible(t_philo *args);

/* ***************Forks***************** */

void		take_forks_dispatcher(t_philo *dinner);
void		take_forks(t_gen_var *gen, t_philo *args, int f1, int f2);
void		drop_forks(t_gen_var *gen, t_philo *args, int f1, int f2);

/* ***************Logs****************** */
void		fork_log(t_philo *dinner, size_t action);
void		eating_log(t_philo *dinner);
void		sleeping_log(t_philo *dinner);
void		thinking_log(t_philo *dinner);
void		died_log(t_philo *dinner);

#endif