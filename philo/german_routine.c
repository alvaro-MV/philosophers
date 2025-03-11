#include "philo.h"


static void	join_threads(t_meeting *meeting)
{
	size_t	i;

	i = 0;
	while (i < meeting->philo_count)
	{
		pthread_join(meeting->realities[i], NULL);
		i++;
	}
}

static void	send_stop_signal(t_meeting *meeting)
{
	size_t	i;

	i = 0;
	while (i < meeting->philo_count)
	{
		meeting->philosophers[i].stop = 1;
		i++;
	}
	usleep(1000);
}

static int	ate_enough(t_meeting *meeting)
{
	size_t	i;
	int		stop;

	if (meeting->args.servings_to_satiate == -1)
		return (0);
	i = 0;
	stop = 1;
	while (i < meeting->philo_count && stop)
	{
		stop = stop && (ssize_t)meeting->philosophers[i].n_servings
			>= meeting->args.servings_to_satiate;
		i++;
	}
	return (stop);
}

void	observe_philosophers(t_meeting *meeting)
{
	size_t	elapsed_ms;
	int		stop;
	size_t	i;

	stop = 0;
	while (!stop)
	{
		if (0 != usleep(100))
			meeting->err = 1;
		stop = ate_enough(meeting);
		stop = stop || meeting->err;
		i = 0;
		while (i < meeting->philo_count && !stop)
		{
			check_death(meeting, i, &stop);
			elapsed_ms = get_elapsed_ms(meeting->philosophers[i].born_time);
			i++;
		}
		i--;
	}
	write(2, "Syscall err\n", 13 * meeting->err);
	send_stop_signal(meeting);
	if (stop == 2)
		printf("%u %u died\n", (unsigned int)elapsed_ms, (unsigned int)i + 1);
	join_threads(meeting);
}
