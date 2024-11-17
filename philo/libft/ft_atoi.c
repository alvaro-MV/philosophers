#include "libft.h"

int	ft_atoi(const char *str)
{
	int     signo;
	int     value;

	value = 0;
	signo = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
			str++;
	if (*str == '-' || *str == '+')
	{
			if (*str == '-')
					signo++;
			str++;
	}
	while (*str >= '0' && *str <= '9')
	{
			value = (*str - '0') + value * 10;
			str++;
	}
	if (signo % 2 != 0)
			value *= -1;
	return (value);
}