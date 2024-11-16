#include "philo.h"

int	compatible(t_philo *args)
{
	t_general_vars gen;

	gen = args->general_vars;
	if (!gen.forks_used[args->tid])
	{
		if (!gen.forks_used[(args->tid + 1) % gen.n_philo])
			return (1);
	}
	return (0);
}

unsigned long long	sleep_routine(t_philo *args, unsigned long timestamp)
{
	usleep(args->general_vars.time_to_sleep);
	sleeping_log(timestamp, args);
}

unsigned long long	think_routine(t_philo *args, unsigned long timestamp)
{
	usleep(1); //Thinking que pongo weyyy
	thinking_log(timestamp, args);
}

unsigned long long	eat_routine(t_philo *args)
{
	unsigned long long	timestamp;
	t_general_vars		gen;

	pthread_mutex_lock(args->general_vars.proc_mutex);

	if (!compatible(args))
		manage_usleep(WAI_T);
	gen = args->general_vars;
	timestamp = get_actual_time();
	pthread_mutex_lock(&gen.proc_mutex[args->tid]);
	take_fork_log(timestamp, args);
	args->general_vars.forks_used[args->tid] = 1;
	pthread_mutex_lock(&gen.proc_mutex[(args->tid + 1) % gen.n_philo]);
	take_fork_log(timestamp, args);
	gen.forks_used[(args->tid) % gen.n_philo] = 1;

	pthread_mutex_unlock(args->general_vars.proc_mutex);
	return (timestamp);
}

void	*philo_routine(void *vargs)
{
	t_philo				*args;
	unsigned long long	timestamp;
	int					i;

	args = (t_philo *) vargs;
	i = 0;
	while (i++ < args->general_vars.n_of_eats)
	{
		timestamp = eat_routine(args);
		eating_log(timestamp, args);
		sleep_routine(args, timestamp);
		think_routine(args, timestamp);//Thinking que pongo weyyy
	}
}
