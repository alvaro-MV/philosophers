/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llutoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:48:21 by alvmoral          #+#    #+#             */
/*   Updated: 2025/02/10 13:48:22 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long long	get_len(unsigned long long nb)
{
	unsigned long long	holder;
	unsigned long long	hex;

	holder = nb;
	hex = 10;
	while (holder > 0)
	{
		holder /= 10;
		hex *= 10;
	}
	return (hex / 100);
}

int	ft_llutoa_w(unsigned long long nb)
{
	unsigned long long	len;
	unsigned long long	digito;
	unsigned char		print_digit;
	int					contador;

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
