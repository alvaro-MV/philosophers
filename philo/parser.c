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

void	parse_input(t_gen_var *general_vars, char **argv)
{
	if (is_in_range_of_uint(argv[0]) && is_in_range_of_ulong(argv[1]))
	{
		general_vars->n_philo = ft_atoui(argv[0]);
		if (general_vars->n_philo > MAX_PHILOS) //testeo
			exit (-1);
		general_vars->time_to_die = ft_atoul(argv[1]);
	}
	else
		exit (-1);
	if (is_in_range_of_ulong(argv[2]) && is_in_range_of_ulong(argv[3]))
	{
		general_vars->time_to_eat = ft_atoul(argv[2]);
		general_vars->time_to_sleep = ft_atoul(argv[3]);
	}
	else
		exit (-1);
	if (argv[4])
	{
		if (is_in_range_of_ulong(argv[4]))
		{
			general_vars->max_meals = ft_atoui(argv[4]);
			general_vars->run_4ever = 0;
		}
		else
			exit(-1);
	}
	else
		general_vars->run_4ever = 1;
	general_vars->philo_alive = general_vars->n_philo;
	write(1, "Franciso Javier", 16);
}

//int	main(int argc, char **argv)
//{
	//t_general_vars	general_vars;
	
	//if (argc < 5 || argc > 6)
	//{
		//write(1, "Format: ./philo <n_philo> <time_to_die> <time_to_eat>", 54);
		//write(1, " <time_to_sleep> [n_times_must_eat]", 35);
		//exit(1);
	//}
	//argv++;
	//parse_input(&general_vars, argv);
	//printf("gen->n_philo: %u\n", general_vars.n_philo);
	//printf("gen->time_to_die: %llu\n", general_vars.time_to_die);
	//printf("gen->time_to_eat: %llu\n", general_vars.time_to_eat);
	//printf("gen->time_to_sleep: %llu\n", general_vars.time_to_sleep);
	//if (argc  == 6)
		//printf("gen->n_of_eats: %u\n", general_vars.n_of_eats);
//}