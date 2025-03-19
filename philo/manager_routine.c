/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:41:04 by alvmoral          #+#    #+#             */
/*   Updated: 2025/03/19 12:37:41y alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_died_routine(t_philo *arr_dinner, int i)
{
	died_log(&arr_dinner[i]);
	return (NULL);
}

int	check_philos_end_eating(t_philo *arr_dinner)
{
	size_t			stop;
	size_t			j;

	j = 0;
	stop = 1;
	while (j < arr_dinner->gen_vars->n_philo && stop)
	{
		stop = arr_dinner[j].n_of_meals >= arr_dinner[j].gen_vars->max_meals;
		j++;
	}
	if (stop)
		return (0);
	return (1);
}

int	check_live(t_philo *arr_dinner, unsigned int *i, pthread_t *philo)
{
	uint64_t		diff_time;
	size_t			j;

	if (!check_philos_end_eating(arr_dinner))
		return (0);
	j = 0;
	pthread_mutex_lock(&arr_dinner->last_meal_mutex);
	diff_time = time_diff_usecs(arr_dinner[*i].time_last_meal);
	pthread_mutex_unlock(&arr_dinner->last_meal_mutex);
	if (diff_time >= arr_dinner[*i].gen_vars->time_to_die)
	{
		while (j < arr_dinner->gen_vars->n_philo)
		{
			arr_dinner[j].not_dead = 0;
			printf("id: %zu\n", j);
			j++;
		}
		j = 0;
		while (j < arr_dinner->gen_vars->n_philo)
			pthread_detach(philo[j++]);
		arr_dinner->gen_vars->philo_alive--;
		philo_died_routine(arr_dinner, *i);
		return (0);
	}
	return (1);
}

void	*manager_routine(void *vargs, pthread_t *philo)
{
	t_philo			*arr_dinner;
	unsigned int	i;
	unsigned int	n_dead;

	arr_dinner = (t_philo *) vargs;
	n_dead = -1;
	manage_usleep(2);
	while (n_dead != arr_dinner->gen_vars->n_philo)
	{
		n_dead = 0;
		i = -1;
		pthread_mutex_lock(&arr_dinner->gen_vars->logs_mutex);
			// write(1, "pero como no va a entra hijo de puta\n", 38);
		while (++i < arr_dinner->gen_vars->n_philo)
		{
			if (arr_dinner[i].not_dead && !check_live(arr_dinner, &i, philo))
			{
				n_dead = arr_dinner->gen_vars->n_philo;
				// pthread_mutex_unlock(&arr_dinner->gen_vars->logs_mutex);
				break ;
			}
			n_dead += !arr_dinner[i].not_dead;
		}
		pthread_mutex_unlock(&arr_dinner->gen_vars->logs_mutex);
	}
	return (wait_philos(arr_dinner, philo), NULL);
}
