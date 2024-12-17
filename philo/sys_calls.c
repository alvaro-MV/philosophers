#include "philo.h"
#include <unistd.h>

void	manage_usleep(__useconds_t	miliseconds)
{
	unsigned int	time;

	time = miliseconds * 1000;
	if (usleep(time - 600) == -1)
		exit (-1);  //Tiene que cancelar los hilos y liberar memoria de todos.
}
