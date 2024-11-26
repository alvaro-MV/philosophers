#include "philo.h"
#include <unistd.h>

void	manage_usleep(__useconds_t	usenconds)
{
	unsigned int	time_to_sleep;

	time_to_sleep = usenconds * 1000;
	if (usleep(time_to_sleep) == -1)
		exit (-1);  //Tiene que cancelar los hilos y liberar memoria de todos.
}
