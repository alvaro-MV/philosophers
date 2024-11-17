/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 20:53:59 by alvmoral          #+#    #+#             */
/*   Updated: 2024/11/17 12:25:47 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int      get_len(int nb)
{
        long    number;
        long    dec;

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

void    ft_putnbr_fd(int n, int fd)
{
        int             dlen;
        int             i;
        int             digit;
        long    lnb;
        char    printn;

        dlen = get_len(n);
        lnb = (long) n;
        i = 0;
        if (lnb < 0)
        {
                write(fd, "-", 1);
                lnb *= -1;
        }
        while (dlen > 0)
        {
                digit = lnb / dlen;
                printn = digit + '0';
                write(fd, &printn, 1);
                lnb -= digit * dlen;
                i = i + 1;
                dlen /= 10;
        }
}