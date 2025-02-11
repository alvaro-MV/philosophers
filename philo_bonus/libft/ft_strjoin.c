/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:00:51 by alvmoral          #+#    #+#             */
/*   Updated: 2024/04/01 17:04:56 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	l1;
	size_t	l2;
	size_t	lt;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	lt = l1 + l2;
	ptr = (char *) malloc(lt * sizeof(char) + 1);
	if (ptr == NULL)
		return (NULL);
	while (*s1)
		*ptr++ = *s1++;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	return (ptr - lt);
}
