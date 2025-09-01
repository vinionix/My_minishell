CC = cc
FLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a

FUNCTIONS = Builtins/builtins.c \
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
			Parsing/ft_utils2.c \
			Parsing/print_error.c \
			Parsing/ft_error.c \
			Parsing/ft_error2.c \
			Parsing/ft_lexer.c \
			Parsing/tokenizer.c \
			Parsing/format_input.c \
			Parsing/quotes_handler.c \
			Parsing/reset.c \
			Parsing/expansion_and_quotes_validation.c \
			Parsing/expansion/export_utils.c \
			Parsing/expansion/expansion_utils.c \
			Parsing/expansion/expansion_utils2.c \
			Parsing/expansion/expansion_utils3.c \
			Parsing/expansion/expansion_utils4.c \
			Parsing/expansion/expansion.c \
			Parsing/expansion/change_env_variable.c \
			Tree_struct/tree_utils.c \
			Tree_struct/tree_create.c \
     		Tree_struct/free_tree.c \
     		Tree_struct/check_priority.c \
     		Tree_struct/search.c \
     		Tree_struct/node_creator.c \
			Signal/signal.c \
			Exorcise/execution.c \
			Exorcise/pipe.c \
			Exorcise/pipe_utils.c \
			Exorcise/find_path.c \
			Exorcise/heredoc.c \
			Exorcise/if_redirect.c \
			Exorcise/solo_redirect.c \
			Exorcise/process.c \
			Exorcise/execution_utils.c \
			Exorcise/exec.c \
			Main/utils.c

FUNCTIONS_BONUS = bonus/Builtins/builtins_bonus.c \
						bonus/Builtins/env_builtins_bonus.c \
						bonus/Builtins/builtins_utils_bonus.c \
						bonus/Builtins/builtins2_bonus.c \
						bonus/Builtins/clean_bonus.c \
						bonus/Builtins/cd_utils_bonus.c \
						bonus/Builtins/exec_builtin_bonus.c \
						bonus/Builtins/unset_bonus.c \
						bonus/Builtins/export_no_args_bonus.c \
						bonus/Parsing/expansion/default_env_bonus.c \
						bonus/Parsing/expansion/env_utils_bonus.c \
						bonus/Parsing/expansion/new_var_parsing_bonus.c \
			bonus/Parsing/ft_utils_bonus.c \
			bonus/Parsing/ft_utils2_bonus.c \
			bonus/Parsing/print_error_bonus.c \
			bonus/Parsing/ft_error_bonus.c \
			bonus/Parsing/ft_error2_bonus.c \
			bonus/Parsing/ft_lexer_bonus.c \
			bonus/Parsing/tokenizer_bonus.c \
			bonus/Parsing/format_input_bonus.c \
			bonus/Parsing/expansion_and_quotes_validation_bonus.c \
			bonus/Parsing/expansion/export_utils_bonus.c \
			bonus/Parsing/expansion/expansion_utils_bonus.c \
			bonus/Parsing/expansion/expansion_utils2_bonus.c \
			bonus/Parsing/expansion/expansion_utils3_bonus.c \
			bonus/Parsing/expansion/expansion_utils4_bonus.c \
			bonus/Parsing/expansion/expansion_bonus.c \
			bonus/Parsing/expansion/change_env_variable_bonus.c \
			bonus/Parsing/subshell/subshell_bonus.c \
			bonus/Parsing/subshell/subshell_utils_bonus.c \
			bonus/Parsing/subshell/copy_tokens_bonus.c \
			bonus/Wildcard/wildcard_bonus.c \
			bonus/Wildcard/wildcard_utils_bonus.c \
			bonus/Wildcard/list_to_matrix_bonus.c \
			bonus/Wildcard/join_matrices_bonus.c \
			bonus/Wildcard/quotes_handler_bonus.c \
			bonus/Wildcard/quotes_utils_bonus.c \
			bonus/Wildcard/wildcard_utils2_bonus.c \
			bonus/Wildcard/wildcard_utils3_bonus.c \
			bonus/Wildcard/read_cd_bonus.c \
			bonus/Wildcard/verify_utils_bonus.c \
			bonus/Wildcard/len_except_bonus.c \
			bonus/Tree_struct/tree_utils_bonus.c \
			bonus/Tree_struct/tree_create_bonus.c \
     		bonus/Tree_struct/free_tree_bonus.c \
     		bonus/Tree_struct/check_priority_bonus.c \
     		bonus/Tree_struct/search_bonus.c \
     		bonus/Tree_struct/node_creator_bonus.c \
			bonus/Signal/signal_bonus.c \
			bonus/Signal/subshell_handler.c \
			bonus/Exorcise/execution_bonus.c \
			bonus/Exorcise/pipe_bonus.c \
			bonus/Exorcise/pipe_utils_bonus.c \
			bonus/Exorcise/find_path_bonus.c \
			bonus/Exorcise/heredoc_bonus.c \
			bonus/Exorcise/if_redirect_bonus.c \
			bonus/Exorcise/and_or_bonus.c \
			bonus/Exorcise/solo_redirect_bonus.c \
			bonus/Exorcise/process_bonus.c \
			bonus/Exorcise/execution_utils_bonus.c \
			bonus/Exorcise/exec_bonus.c \
			bonus/Main/utils_bonus.c

OBJS = $(FUNCTIONS:.c=.o)

OBJS_BONUS = $(FUNCTIONS_BONUS:.c=.o)

NAME_LIB = minishell.a

NAME_LIB_BONUS = minishell_bonus.a

NAME = minishell

NAME_BONUS = minishell_bonus

.c.o:
	@echo -n "|"
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME_LIB) $(NAME)

$(NAME_LIB): $(OBJS) $(LIBFT)
	@ar rcs $@ $(OBJS)

$(NAME_LIB_BONUS): $(OBJS_BONUS) $(LIBFT)
	@ar rcs $@ $(OBJS_BONUS)

$(NAME): $(OBJS) $(LIBFT) $(NAME_LIB)
	@$(CC) $(FLAGS) Main/main.c $(OBJS) -Llibft -lft -lreadline -o $(NAME)
	@echo "\033[46mminiconsha compiled successfully!\033[0m"

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT) $(NAME_LIB_BONUS)
	@$(CC) $(FLAGS) bonus/Main/main_bonus.c $(OBJS_BONUS) -Llibft -lft -lreadline -o $(NAME_BONUS)
	@echo
	@echo "\033[46mminiconsha_bonus compiled successfully!\033[0m"

$(LIBFT):
	@echo
	@make -C libft --no-print-directory

clean:
	@rm -f $(OBJS) $(OBJS_BONUS)
	@make clean -C libft --no-print-directory

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS) $(NAME_LIB) $(NAME_LIB_BONUS)
	@make fclean -C libft --no-print-directory

re: fclean all

bonus: $(NAME_LIB_BONUS) $(NAME_BONUS)

