NAME = philo/philo

SRCS = philo/init.c philo/logs.c philo/main.c philo/manager_routine.c \
	   philo/parser.c philo/philo_routine.c \
	   philo/philo_utils.c philo/sys_calls.c \
	   philo/libft/ft_atoui.c philo/libft/ft_atoul.c philo/libft/ft_calloc.c \
	   philo/libft/ft_itoa.c philo/libft/ft_ptoa.c \
	   philo/libft/ft_utoa.c philo/libft/ft_xtoa.c philo/libft/ft_printf.c \
	   philo/libft/ft_strtoa.c philo/libft/ft_chtoa.c \
	   philo/libft/ft_putnbr.c philo/libft/ft_putstr.c \
	   philo/libft/ft_strlen.c philo/libft/ft_strncmp.c philo/libft/ft_substr.c \
	   philo/libft/ft_free_exit.c philo/libft/ft_llutoa.c 


CC = cc

# Opciones de compilación
CFLAGS = -Wall -Wextra -Werror

# Directorio de archivos fuente
SRCDIR = .

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re