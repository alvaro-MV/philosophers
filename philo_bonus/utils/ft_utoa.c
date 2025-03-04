/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:50:18 by alvaro            #+#    #+#             */
/*   Updated: 2024/11/25 11:41:40 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static unsigned long	get_len(unsigned int nb)
{
	unsigned long	hex;

	hex = 1;
	if (nb == 0)
		hex *= 10;
	while (hex <= nb)
		hex *= 10;
	return (hex / 10);
}

int	ft_utoa_w(unsigned int nb)
{
	unsigned int	len;
	unsigned long	digito;
	unsigned char	print_digit;
	int				contador;

	len = get_len(nb);
	contador = 0;
	while (len > 0)
	{
		digito = nb / len;
		print_digit = digito + '0';
		contador += write(1, &print_digit, 1);
		nb -= digito * len;
		len /= 10;
	}
	return (contador);
}
