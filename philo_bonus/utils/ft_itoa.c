/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:42:14 by alvmoral          #+#    #+#             */
/*   Updated: 2024/04/04 18:17:08 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	get_len(int nb)
{
	long	number;
	long	dec;

	number = (long) nb;
	dec = 1;
	if (number < 0)
		number *= -1;
	if (number == 0)
		dec *= 10;
	while (dec <= number)
		dec *= 10;
	return (dec / 10);
}

static int	get_memory(int nb)
{
	long	number;
	long	dec;
	int		contador;

	number = (long) nb;
	dec = 1;
	contador = 0;
	if (number < 0)
	{
		number *= -1;
		contador++;
	}
	if (number == 0)
		return (1);
	while (dec <= number)
	{
		contador++;
		dec *= 10;
	}
	return (contador);
}

static void	loop(char *ptr, long dlen, long lnb, int *i)
{
	int	digit;

	while (dlen > 0)
	{
		digit = lnb / dlen;
		ptr[*i] = digit + '0';
		lnb -= digit * dlen;
		*i = *i + 1;
		dlen /= 10;
	}
}

char	*ft_itoa(int nb)
{
	int		dlen;
	int		i;
	long	lnb;
	char	*ptr;

	dlen = get_len(nb);
	lnb = (long) nb;
	i = 0;
	ptr = (char *) malloc(get_memory(nb) + 1);
	if (ptr == NULL)
		return (NULL);
	if (lnb < 0)
	{
		ptr[i++] = '-';
		lnb *= -1;
	}
	loop(ptr, dlen, lnb, &i);
	ptr[i] = '\0';
	return (ptr);
}

// int	main(void)
// {
// 	char	*num = ft_itoa(0);

// 	printf("%s\n", num);
// 	free(num);
// }
