#include "../consha.h"

bool	not_interpret(const char *input, int i)
{
	if (i > 0)
	{
		if (input[i - 1] == '\\')
			return (true);
	}
	return (false);
}

int	chr_separator(char *input, int i)
{
	if (not_interpret(input, i))
		return (0);
	if (input[i] == '&' && input[i + 1] == '&')
		return (1);
	else if (input[i] == '|' && input[i + 1] == '|')
		return (2);
	else if (input[i] == '>' && input[i + 1] == '>')
		return (3);
	else if (input[i] == '<' && input[i + 1] == '<')
		return (4);
	else if (input[i] == '|')
		return (5);
	else if (input[i] == '>')
		return (6);
	else if (input[i] == '<')
		return (7);
	else if (input[i] == '(')
		return (8);
	else if (input[i] == ')')
		return (9);
	return (0);
}

int	ft_len_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

int	jump_char(char chr)
{
	if (chr == ' ' || chr == '\t')
		return (1);
	if (chr == '"')
		return (2);
	if (chr == '\'')
		return (3);
	return (0);
}

void	free_split(char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		free(input[i]);
		i++;
	}
	free(input);
}

void	free_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].value || tokens[i].type == TK_SUBSHELL)
	{
		if (tokens[i].type == TK_SUBSHELL)
			free_tokens(tokens[i].subshell);
		else
			free(tokens[i].value);
		i++;
	}
	free(tokens);
}
