/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:50:43 by alvmoral          #+#    #+#             */
/*   Updated: 2025/02/10 13:50:44 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>

void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
unsigned int		ft_atoui(const char *str);
unsigned long long	ft_atoul(const char *str);
size_t				ft_strlen(const char *s);
int					ft_strncmp(char *s1, char *s2, unsigned int n);
void				*ft_calloc(size_t count, size_t size);
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				ft_free_exit(void *ptr);

int					ft_chtoa_w(unsigned int c);
int					ft_xtoa_w(unsigned int nb, char c);
int					ft_utoa_w(unsigned int nb);
int					ft_strtoa_w(char *str);
int					ft_ptoa_w(unsigned long long nb);
int					ft_itoa_w(int nb);
int					ft_llutoa_w(unsigned long long nb);
int					ft_printf(char const *s1, ...);

#endif
