#include "philo.h"
#include <unistd.h>

void	manage_usleep(__useconds_t	usenconds)
{
	if (usleep(usenconds) == -1)
		exit (-1);  //Tiene que cancelar los hilos y liberar memoria de todos.
}
