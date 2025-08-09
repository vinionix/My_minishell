CC = cc
FLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a

FUNCTIONS = Tester/debug.c \
            Builtins/builtins.c \
						Builtins/env_builtins.c \
						Builtins/builtins_utils.c \
						Builtins/builtins2.c \
						Builtins/clean.c \
						Builtins/cd_utils.c \
						Builtins/exec_builtin.c \
						Builtins/unset.c \
						Builtins/export_no_args.c \
						Parsing/expansion/default_env.c \
						Parsing/expansion/env_utils.c \
						Parsing/expansion/new_var_parsing.c \
			Parsing/ft_utils.c \
			Parsing/ft_error.c \
			Parsing/ft_lexer.c \
			Parsing/tokenizer.c \
			Parsing/expansion_and_quotes_validation.c \
			Parsing/expansion/export_utils.c \
			Parsing/expansion/expansion_utils.c \
			Parsing/expansion/expansion.c \
			Parsing/expansion/change_env_variable.c \
			Wildcard/wildcard.c \
			Wildcard/wildcard_utils.c \
			Wildcard/list_to_matrix.c \
			Wildcard/join_matrices.c \
			Wildcard/quotes_handler.c \
			Wildcard/quotes_utils.c \
			Wildcard/wildcard_utils2.c \
			Wildcard/read_cd.c \
			Wildcard/verify_utils.c \
			Wildcard/len_except.c \
			Tree_struct/tree_utils.c \
			Tree_struct/tree_create.c \
     	Tree_struct/free_tree.c \
			Exorcise/execution.c \
			Exorcise/pipe.c \
			Exorcise/find_path.c \
			Exorcise/heredoc.c

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
