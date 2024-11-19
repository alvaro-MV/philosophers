#include "philo.h"

unsigned long long	sleep_routine(t_philo *args)
{
	usleep(args->general_vars->time_to_sleep);
	pthread_mutex_lock(&args->general_vars->logs_mutex);
	sleeping_log(args);
	pthread_mutex_unlock(&args->general_vars->logs_mutex);
}

unsigned long long	think_routine(t_philo *args)
{
	usleep(1); //Thinking que pongo weyyy
	pthread_mutex_lock(&args->general_vars->logs_mutex);
	thinking_log(args);
	pthread_mutex_unlock(&args->general_vars->logs_mutex);
}


unsigned long long	eat_routine(t_philo *args)
{
	usleep(args->general_vars->time_to_eat);
	pthread_mutex_lock(&args->general_vars->logs_mutex);
	args->time_last_meal = get_actual_time();
	eating_log(args);
	pthread_mutex_unlock(&args->general_vars->logs_mutex);
}

void	take_forks(t_philo *args)
{
	t_gen_var		*gen;

	gen = args->general_vars;
	pthread_mutex_lock(&gen->proc_mutex);

	if (!compatible(args))
		manage_usleep(WAI_T);
	pthread_mutex_lock(&gen->forks[args->tid]);
	take_fork_log(args);
	gen->forks_used[args->tid] = 1;
	pthread_mutex_lock(&gen->forks[(args->tid + 1) % gen->n_philo]);
	take_fork_log(args);
	gen->forks_used[(args->tid) % gen->n_philo] = 1;

	pthread_mutex_unlock(&gen->proc_mutex);
}

void	*philo_routine(void *vargs)
{
	t_philo				*args;
	unsigned long long	timestamp;
	int					i;

	args = (t_philo *) vargs;
	i = 0;
	while (i++ < args->general_vars->n_of_eats)
	{
		//take_forks(args);
		eat_routine(args);
		sleep_routine(args);
		think_routine(args);//Thinking que pongo weyyy
	}
	return (NULL);
}
