#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <limits.h>


void    			ft_putstr_fd(char *s, int fd);
void    			ft_putnbr_fd(int n, int fd);
unsigned int		ft_atoui(const char *str);
unsigned long long	ft_atoul(const char *str);
int					ft_atoi(const char *str);
size_t  			ft_strlen(const char *s);
void				*ft_calloc(size_t count, size_t size);
char				*ft_substr(char const *s, unsigned int start, size_t len);

#endif