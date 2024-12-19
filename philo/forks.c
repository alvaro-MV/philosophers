#include "philo.h"

void	take_forks(t_gen_var *gen, t_philo *args, int f1, int f2)
{
	pthread_mutex_lock(&gen->forks[f1]);
	pthread_mutex_lock(&gen->logs_mutex);
	fork_log(args, 1);
	pthread_mutex_unlock(&gen->logs_mutex);

	pthread_mutex_lock(&gen->forks[f2]);
	pthread_mutex_lock(&gen->logs_mutex);
	if (args->general_vars->n_philo == 1)
	{
		pthread_mutex_unlock(&gen->forks[f2]);
		pthread_mutex_unlock(&gen->forks[f1]);
		return ;
	}
	fork_log(args, 1);
	pthread_mutex_unlock(&gen->logs_mutex);
}

void	drop_forks(t_gen_var *gen, t_philo *args, int f1, int f2)
{
	pthread_mutex_unlock(&gen->forks[f1]);
	fork_log(args, 0);
	pthread_mutex_unlock(&gen->forks[f2]);
	fork_log(args, 0);
}

void	take_forks_dispatcher(t_philo *args)
{
	t_gen_var		*gen;

	gen = args->general_vars;
	if (args->tid % 2 && args->general_vars->n_philo % 2 == 0)
		take_forks(gen, args, args->tid % gen->n_philo, args->tid - 1);
	else
		take_forks(gen, args, args->tid - 1, args->tid % gen->n_philo);
}