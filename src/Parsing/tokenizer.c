#include "../consha.h"

static t_token	*create_tokens(char **matrix)
{
	t_token	*tokens;
	int		i;

	i = 0;
	if (matrix == NULL)
		return (NULL);
	tokens = (t_token *)malloc(sizeof(t_token) * (ft_len_matrix(matrix) + 1));
	while (matrix[i])
	{
		tokens[i].value = ft_strdup(matrix[i]);
		tokens[i].id = i;
		tokens[i].passed = -1;
		tokens[i].subshell = NULL;
		i++;
	}
	tokens[i].value = NULL;
	tokens[i].id = 0;
	tokens[i].passed = 0;
	tokens[i].type = -1;
	tokens[i].subshell = NULL;
	return (tokens);
}

void	ignore_backslash_quotes(char *input)
{
	int i = 0;
	while (input[i])
	{
		if (input[i] == '\'' && not_interpret(input, i))
			input[i] = SINGLE_QUOTE_MARKER;
		else if (input[i] == '\"' && not_interpret(input, i))
			input[i] = DOUBLE_QUOTE_MARKER;
		i++;
	}
}

int	tokenizer(t_arg_main *args)
{
	args->temp = format_input(args->rdline);
	if (args->temp == NULL)
		return (1);
	ignore_backslash_quotes(args->temp);
	args->matrix = ft_split(args->temp, ' ');
	args->tokens = create_tokens(args->matrix);
	if (args->temp != NULL)
		free(args->temp);
	ft_lexer(&args->tokens);
	if (sintaxe_error(&args->tokens) == 1)
	{
		free_tokens(args->tokens);
		free_split(args->matrix);
		return (1);
	}
	creat_subshell(&args->tokens);
	tree_creator(&args->tokens, &args->tree, -1);
	get_data()->head = args->tree;
	return (0);
}
