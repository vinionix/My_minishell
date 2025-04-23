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
	$(CC) $(FLAGS) main.c $(OBJS) -Llibft -lft -lreadline -o minishell

$(LIBFT):
	make -C libft
clean:
	rm -f $(OBJS)
	make clean -C libft
fclean: clean
	rm -f $(NAME) $(OBJS)
	make fclean -C libft
re: fclean all
