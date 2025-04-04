/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:32:29 by alvmoral          #+#    #+#             */
/*   Updated: 2025/03/04 15:32:31 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

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
char				*ft_strjoin(char const *s1, char const *s2);
void				*ft_calloc(size_t count, size_t size);
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				ft_free_exit(void *ptr);

int					ft_chtoa_w(unsigned int c);
int					ft_xtoa_w(unsigned int nb, char c);
int					ft_utoa_w(unsigned int nb);
int					ft_strtoa_w(char *str);
int					ft_ptoa_w(unsigned long long nb);
int					ft_itoa_w(int nb);
char				*ft_itoa(int nb);
int					ft_llutoa_w(unsigned long long nb);
int					ft_printf(char const *s1, ...);

#endif
