#include "wildcard.h"

int	count_quotes_right(char *str, char c)
{
	int	i;
	int	size;

	i = -1;
	size = 0;
	while (str[++i])
	{
		if (str[i] == c)
			size++;
	}
	return (size);
}

int	count_quotes_left(char *str, int i, char c)
{
	int	size;

	size = 0;
	while (i != -1)
	{
		if (str[i] == c)
			size++;
		i--;
	}
	return (size);
}

static void	turn_into_meta(char *str, char quote_type, int *i)
{
	(*i)++;
	while (str[*i] && str[*i] != quote_type)
	{
		if (str[*i] == '\'')
			str[*i] = SINGLE_QUOTE_MARKER;
		else if (str[*i] == '\"')
			str[*i] = DOUBLE_QUOTE_MARKER;
		(*i)++;
	}
	if (str[*i])
		(*i)++;
}

static void	do_not_expand(char **matrix)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (matrix[++i])
	{
		while (matrix[i][j])
		{
			if (matrix[i][j] == '$')
			{
				if ((count_quotes_right(matrix[i] + j, '\'') % 2 != 0
					&& count_quotes_left(matrix[i], j, '\'') % 2 != 0)
					|| not_interpret(matrix[i], j))
				matrix[i][j] = DOLLAR_MARKER;
			}
			else if (matrix[i][j] == '*')
			{
				if (((count_quotes_right(matrix[i] + j, '\'') % 2 != 0
					&& count_quotes_left(matrix[i], j, '\'') % 2 != 0)
						|| (count_quotes_right(matrix[i] + j, '\"') % 2 != 0
							&& count_quotes_left(matrix[i], j, '\"') % 2 != 0))
					|| not_interpret(matrix[i], j))
				matrix[i][j] = EXPANSION_MARKER;
			}
			j++;
		}
		j = 0;
	}
}

void	parse_quotes(char **matrix)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (matrix[++i])
	{
		while (matrix[i][j])
		{
			if (matrix[i][j] == '\'')
				turn_into_meta(matrix[i], '\'', &j);
			else if (matrix[i][j] == '\"')
				turn_into_meta(matrix[i], '\"', &j);
			else
				j++;
		}
		j = 0;
	}
	do_not_expand(matrix);
}
