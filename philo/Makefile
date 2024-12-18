NAME = philo

SRCS = init.c logs.c main.c manager_routine.c \
	   parser.c philo_routine.c \
	   philo_utils.c sys_calls.c \
	   libft/ft_atoui.c libft/ft_atoul.c libft/ft_calloc.c \
	   libft/ft_itoa.c libft/ft_ptoa.c \
	   libft/ft_utoa.c libft/ft_xtoa.c libft/ft_printf.c \
	   libft/ft_strtoa.c libft/ft_chtoa.c \
	   libft/ft_putnbr.c libft/ft_putstr.c \
	   libft/ft_strlen.c libft/ft_strncmp.c libft/ft_substr.c \
	   libft/ft_free_exit.c libft/ft_llutoa.c 


CC = cc

# Opciones de compilación
CFLAGS = -Wall -Wextra -Werror -g

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