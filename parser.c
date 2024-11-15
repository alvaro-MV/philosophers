#include "philo.h"

int	main(int argc, char **argv)
{
	if (argc < 5)
	{
		write(1, "Format: ./philo <n_philo> <time_to_die> <time_to_eat>", 54);
		write(1, "<time_to_sleep> [n_times_must_eat]", 35);
		exit(1);
	}
	
}

//Como parsear la movida: Fácil
//
//1. Uno para numerico. Ni comas ni nada.
//
//2. Uno para parsear a el tiempo que recibe usleep.
//
//3. 
