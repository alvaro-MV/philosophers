#include "philo.h"
#include <unistd.h>

void	manage_usleep(__useconds_t	miliseconds)
{
	unsigned int	time_to_sleep;

	time_to_sleep = miliseconds * 1000;
	if (usleep(time_to_sleep) == -1)
		exit (-1);  //Tiene que cancelar los hilos y liberar memoria de todos.
}
