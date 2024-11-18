#include "libft.h"

void	ft_free_exit(void *ptr)
{
	free(ptr);
	exit(-1);
}