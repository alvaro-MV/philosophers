NAME = philo

SRCS = init.c logs.c main.c manager_routine.c \
	   parser.c philo_routine.c \
	   philo_utils.c sys_calls.c forks.c \
	   utils/ft_atoui.c utils/ft_atoul.c utils/ft_calloc.c \
	   utils/ft_itoa.c utils/ft_ptoa.c \
	   utils/ft_utoa.c utils/ft_xtoa.c utils/ft_printf.c \
	   utils/ft_strtoa.c utils/ft_chtoa.c \
	   utils/ft_putnbr.c utils/ft_putstr.c \
	   utils/ft_strlen.c utils/ft_strncmp.c utils/ft_substr.c \
	   utils/ft_free_exit.c utils/ft_llutoa.c 


CC = cc

# Opciones de compilación
CFLAGS = -Wall -Wextra -Werror -g -pthread -fsanitize=thread

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

norm:
	@norminette *.c
	@norminette */*.c
	@norminette *.h
	@norminette */*.h

.PHONY: all clean fclean re
