#include "libft.h"

static void	ft_bzero(void *s, size_t n)
{
	if (n > 0)
	{
		while (n--)
		{
			*(char *) s = 0;
			s++;
		}
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void    *ptr;

	if (count && size && SIZE_MAX / count < size)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}