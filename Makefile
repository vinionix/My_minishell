CC = cc
FLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a

FUNCTIONS = Tester/debug.c \
            Builtins/builtins.c \
			Parsing/ft_utils.c \
			Parsing/ft_error.c \
			Parsing/ft_lexer.c

OBJS = $(FUNCTIONS:.c=.o)

NAME_LIB = minishell.a

NAME = minishell

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME_LIB) $(NAME)

$(NAME_LIB): $(OBJS) $(LIBFT)
	ar rcs $@ $(OBJS)

$(NAME): $(OBJS) $(LIBFT) $(NAME_LIB)
	$(CC) $(FLAGS) Tester/main.c $(OBJS) -Llibft -lft -lreadline -o $(NAME)

$(LIBFT):
	make -C libft

clean:
	rm -f $(OBJS)
	make clean -C libft

fclean: clean
	rm -f $(NAME) $(NAME_LIB)
	make fclean -C libft

re: fclean all