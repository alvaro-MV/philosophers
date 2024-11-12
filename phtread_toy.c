#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>// The POSIX standard header for using pthread library
#include <pthread.h>// The semaphores are not exposed through pthread.h
#include <semaphore.h>// The main pointer addressing a semaphore object used
#include <unistd.h>
#include <sys/types.h>

void    ft_putnbr_fd(int n, int fd);

int	fran_javi = 0;

typedef struct s_r_w_vars
{
	size_t	readers;
	size_t	writers;
	sem_t	mutex;
	sem_t	readers_sem;
}			t_r_w_vars;

void	readers_log(t_r_w_vars	*rvars)
{

	sem_wait(&rvars->mutex);
	write(1, "[READER] thread id ==> ", 24);
	ft_putnbr_fd(gettid(), 1);	
	write(1, " || fran_javi = ", 17);
	ft_putnbr_fd(fran_javi, 1);
	write(1, "\n", 1);
	sem_post(&rvars->mutex);
}

void	*_readers_(void *vars)
{
	t_r_w_vars	*rvars = (t_r_w_vars *) vars;

	sem_wait(&rvars->mutex);
	rvars->readers++;
	if (rvars->readers == 1)
	{
		sem_wait(&rvars->readers_sem);
	}
	sem_post(&rvars->mutex);
	readers_log(rvars);
	sem_wait(&rvars->mutex);
	ft_putnbr_fd(rvars->readers, 1);
	rvars->readers--;
	if (rvars->readers == 0)
		sem_post(&rvars->readers_sem);
	sem_post(&rvars->mutex);
	return (NULL);
}

void	writers_log(t_r_w_vars	*rvars)
{
	sem_wait(&rvars->mutex);
	write(1, "[WRITER] thread id ==> ", 24);
	ft_putnbr_fd(gettid(), 1);	
	write(1, " || fran_javi = ", 17);
	ft_putnbr_fd(fran_javi, 1);
	write(1, "\n", 1);
	sem_post(&rvars->mutex);
}

void	*_writers_(void *vars)
{
	t_r_w_vars	*wvars = (t_r_w_vars *) vars;
	sem_wait(&wvars->readers_sem);
	fran_javi++;
	writers_log(wvars);
	sem_post(&wvars->readers_sem);
	return (NULL);
}

int	main(void)
{
	pthread_t	readers[5];
	pthread_t	writers[2];
	t_r_w_vars	vars;

	sem_init(&vars.mutex, 0, 1);
	sem_init(&vars.readers_sem, 0, 1);
	vars.readers = 0;
	vars.writers = 0;
	int	i = 0;
	while (i < 5)
	{
		if (pthread_create(&readers[i++], NULL, _readers_, &vars))
		{
			write(1, "Mala creasion\n", 15);
			exit(-1);
		}
	}
	i = 0;
	while (i < 2)
	{
		if (pthread_create(&writers[i++], NULL, _writers_, &vars))
			(write(1, "Mala creasion\n", 15), exit(-1));
	}
	i = 0;
	while (i < 5)
	{
		pthread_join(readers[i], NULL);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		pthread_join(writers[i], NULL);
		i++;
	}
	return (0);
}
