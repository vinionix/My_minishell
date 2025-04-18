CC = cc

FLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a

FUNCTIONS = debug.c \
			parsing.c

OBJS = $(FUNCTIONS:.c=.o)

NAME = minishell

.c.o:
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)



$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) main.c $(LIBFT) $(OBJS) -lreadline

$(LIBFT):
	make -C libft
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME) $(OBJS)
re: fclean all
