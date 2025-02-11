/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:53:08 by alvaro            #+#    #+#             */
/*   Updated: 2024/11/26 22:45:57 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	write_arguments(char const *s1, va_list argum, int *counter)
{
	char	format;

	format = *s1;
	if (format == 'u')
		*counter += ft_utoa_w(va_arg(argum, unsigned int));
	else if (format == 'x' || format == 'X')
		*counter += ft_xtoa_w(va_arg(argum, unsigned int), format);
	else if (format == 'p')
		*counter += ft_ptoa_w(va_arg(argum, unsigned long long));
	else if (format == 's')
		*counter += ft_strtoa_w(va_arg(argum, char *));
	else if (format == 'c')
		*counter += ft_chtoa_w(va_arg(argum, int));
	else if (format == 'i' || format == 'd')
		*counter += ft_itoa_w(va_arg(argum, int));
	else if (format == 'l')
		*counter += ft_llutoa_w(va_arg(argum, unsigned long long));
	else if (format == '%')
		*counter += write(1, &format, 1);
	else
		return ;
}

int	ft_printf(char const *s1, ...)
{
	int		counter;
	int		control;
	size_t	i;
	va_list	argum;

	i = 0;
	counter = 0;
	va_start(argum, s1);
	while (s1[i])
	{
		if (s1[i] == '%' && s1[i++] != '\0')
		{
			control = counter;
			write_arguments(&s1[i], argum, &counter);
			if (control > counter)
				return (-1);
		}
		else
			counter += write(1, &s1[i], 1);
		i++;
	}
	va_end(argum);
	return (counter);
}
