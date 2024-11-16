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

unsigned long long	eat_routine(t_philo *args)
{
	unsigned long long	timestamp;

	if (!compatible(args))
		manage_usleep(1);
	timestamp = get_actual_time();
	pthread_mutex_lock(&args->general_vars.proc_mutex[args->tid]);
	take_fork_log(timestamp, args);
	args->general_vars.forks_used[args->tid] = 1;
	pthread_mutex_lock(&args->general_vars.proc_mutex[(args->tid + 1) % 5]);
	take_fork_log(timestamp, args);
	args->general_vars.forks_used[(args->tid) % 5] = 1;
	return (timestamp);
}

void	*philo_routine(void *vargs)
{
	t_philo				*args;
	unsigned long long	timestamp;
	int					i;

	args = (t_philo *) vargs;
	pthread_mutex_lock(args->general_vars.proc_mutex);
	i = 0;
	while (i++ < args->general_vars.n_of_eats)
	{
		timestamp = eat_routine(args);
		eating__log(timestamp, args),
		usleep(args->general_vars.time_to_sleep);
		sleeping_log(timestamp, args),
		usleep(1); //Thinking que pongo weyyy
		thinking_log(timestamp, args);
		pthread_mutex_unlock(args->general_vars.proc_mutex);
	}
}
