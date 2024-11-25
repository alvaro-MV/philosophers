/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:50:02 by alvaro            #+#    #+#             */
/*   Updated: 2024/11/25 11:42:39 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	get_len_hex(unsigned long long nb)
{
	unsigned long long	holder;
	unsigned long long	hex;

	holder = nb;
	hex = 0x01;
	while (holder >= 0x10)
	{
		holder /= 0x10;
		hex *= 0x10;
	}
	return (hex);
}

static int	write_digit(unsigned long long digito)
{
	char	ch;

	if (digito <= 9)
		ch = digito + '0';
	else
	{
		digito = digito - 10;
		ch = digito + 'a';
	}
	return (write(1, &ch, 1));
}

int	ft_ptoa_w(unsigned long long nb)
{
	unsigned long long	len;
	unsigned long long	digito;
	int					contador;

	contador = 0;
	if (nb == 0)
		return (write(1, "(nil)", 5));
	len = get_len_hex(nb);
	contador += write(1, "0x", 2);
	while (len > 0x0)
	{
		digito = nb / len;
		contador += write_digit(digito);
		nb -= digito * len;
		len /= 0x10;
	}
	return (contador);
}
