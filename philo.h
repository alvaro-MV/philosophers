/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:09:15 by alvmoral          #+#    #+#             */
/*   Updated: 2024/11/13 02:17:57 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include "dictionary.h"

typedef struct s_philo	
{
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	*forks;
	int				tid;
	int				*forks_in_use;
}					t_philo;