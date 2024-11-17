#include "libft.h"

unsigned int	ft_atoui(const char *str)
{
	unsigned int     value;

	value = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
			str++;
	while (*str >= '0' && *str <= '9')
	{
			value = (*str - '0') + value * 10;
			str++;
	}
	return (value);
}
