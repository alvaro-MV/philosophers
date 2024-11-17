#include "philo.h"

int	check_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	is_in_range_of_ulong(char *next_n)
{
	size_t				len;
	unsigned long long	max_common;
	char				*ch_number;

	if (!check_number(next_n))
		return (0);
	max_common = 1844674407370955161; //20 dígitos.
	len = ft_strlen(next_n) - 1;
	if (len + 1 > 20) //20 es el numero de digito sde ULLON_MAX
		return (0);
	else if (len + 1 < 20)
		return (1);
	ch_number = ft_substr(next_n, 0, len);
	if (!ch_number)
		return (0);
	if (ft_atoul(ch_number) > max_common) //Crear la function ft_atoul
		return (free(ch_number), 0);
	else if (next_n[len] > '5') //la ultima cifra
		return (free(ch_number), 0);
	else
		return (free(ch_number), 1);
}

int	is_in_range_of_uint(char *next_n)
{
	size_t			len;
	unsigned int	max_common;
	char			*ch_number;

	if (!check_number(next_n))
		return (0);
	len = ft_strlen(next_n) - 1;
	max_common = 429496729;
	if (len + 1 > 10)
		return (0);
	else if (len + 1 < 10)
		return (1);
	ch_number = ft_substr(next_n, 0, len);
	if (!ch_number)
		return (0);
	if (ft_atoui(ch_number) > max_common)
		return (free(ch_number), 0);
	else if (next_n[len] > '5')
		return (free(ch_number), 0);
	else
		return (free(ch_number), 1);
}

// void	parse_input(t_general_vars *general_vars, char *argv)
// {
// 	if (is_in_range_of_uint(argv[0]) && is_in_range_of_ulong(argv[1]))
// 	{
// 		general_vars->n_philo = ft_atou(argv[0]);
// 		if (general_vars->n_philo > MAX_PHILOS) //testeo
// 			exit (-1); //testeo
// 		general_vars->time_to_die = ft_atoul(argv[1]);
// 	}
// 	else
// 		exit (-1);
// 	if (is_in_range_of_ulong(argv[2]) && is_in_range_of_ulong(argv[3]))
// 	{
// 		general_vars->time_to_eat = ft_atoul(argv[2]);
// 		general_vars->time_to_sleep = ft_atoul(argv[3]);
// 	}
// 	else
// 		exit (-1);
// 	if (is_in_range_of_ulong(argv[4]))
// 	{
// 		general_vars->n_of_eats = ft_atou(argv[4]);
// 		return ;
// 	}
// 	exit(-1);
// }

//int	main(void)
//{
	//printf("is in range ulong: %u\n", is_in_range_of_ulong("18446744073709551616"));
//}