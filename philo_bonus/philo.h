/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:41:44 by alvmoral          #+#    #+#             */
/*   Updated: 2025/03/04 15:31:26 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <pthread.h>
# include <aio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <semaphore.h>
# include <unistd.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/time.h>
# include <time.h>
# include <limits.h>
# include <sys/wait.h>
# include "utils/utils.h"

typedef struct s_general_vars
{
	sem_t			*logs_sem;
	sem_t			*forks;
	sem_t			*last_meal_mutex;
	unsigned int	n_philo;
	uint64_t		init_time;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	unsigned int	max_meals;
	int				run_4ever;
}					t_gen_var;

typedef struct s_philo
{
	t_gen_var		*gen_vars;
	int				tid;
	unsigned int	pid;
	unsigned int	n_of_meals;
	uint64_t		time_last_meal;
	pthread_t		manager;
	unsigned int	not_dead;
	unsigned int	all_meals;
}					t_philo;

# define MAX_PHILOS 200
# define WAI_T 13

# define PHILO_DIED 9
# define PHILO_END_EATING 6

// ************Utils*****************

void		manage_usleep(sem_t *logs_sem, __useconds_t miliseconds);
uint64_t	get_actual_time(void);
uint64_t	time_diff_usecs(uint64_t start);
void		parse_input(t_gen_var *gen_vars, char **argv);
void		p_new(t_gen_var *gen_vars, t_philo **dinner);
void		close_sem(sem_t *sem, char *name);
void		wait_philos(t_philo *arr_dinner);

/* 	*************Initialization******* */

int			init_protection_sem(t_gen_var *general_vars);
int			init_forks(t_gen_var *gen_vars);
int			init_args(t_gen_var *gen_vars, t_philo *args);

/* ***************Routines************* */

void		philo_routine(void *vargs);
void		*manager_routine(void *vargs);

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