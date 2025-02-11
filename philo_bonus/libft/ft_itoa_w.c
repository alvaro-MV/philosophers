/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 22:01:37 by alvmoral          #+#    #+#             */
/*   Updated: 2024/11/25 11:43:05 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

int	ft_itoa_w(int nb)
{
	int		dlen;
	int		contador;
	long	lnb;
	int		digit;
	char	printed_digit;

	dlen = get_len(nb);
	lnb = (long) nb;
	contador = 0;
	if (lnb < 0)
	{
		contador += write(1, "-", 1);
		lnb *= -1;
	}
	while (dlen > 0)
	{
		digit = lnb / dlen;
		printed_digit = digit + '0';
		contador += write(1, &printed_digit, 1);
		lnb -= digit * dlen;
		dlen /= 10;
	}
	return (contador);
}

// void	manage_negatives(int *lnb, int *contador)
// {
// 	if (*lnb < 0)
// 	{
// 		*contador += write(1, "-", 1);
// 		*lnb = *lnb * -1;
// 	}
// }

// int	ft_itoa_w(unsigned int nb)
// {
// 	long			digit;
// 	int				dlen;
// 	long			lnb;
// 	unsigned char	print_digit;
// 	int				contador;

// 	lnb = (int) nb;
// 	dlen = get_len(lnb);
// 	contador = 0;
// 	printf("lnb: %li\n", lnb);
// 	manage_negatives(&lnb, &contador);
// 	if (lnb == 2147483648)
// 	while (dlen > 0)
// 	{
// 		digit = lnb / dlen;
// 		//printf("digito: %li,  lnb: %li,  dlen: %i\n", digit ,lnb, dlen);
// 		print_digit = digit + '0';
// 		contador += write(1, &print_digit, 1);
// 		lnb -= digit * dlen;
// 		dlen /= 10;
// 	}
// 	return (contador);
// }