#include "wildcard.h"

void	reset_matches(t_wildcard *list)
{
	while (list)
	{
		list->match = true;
		list->index = 0;
		list = list->next;
	}
}

char	*update_vars(const char *wildcard, t_var *var)
{
	char	*str;

	str = NULL;
	var->start = var->size + 1;
	if (var->start - 1 < (unsigned int)ft_strlen(wildcard))
		var->size = strchr_index_next(wildcard, '*', var->start);
	str = ft_substr(wildcard, var->start, var->size - var->start);
	return (str);
}

void	reset_modified_chars(char **matrix, char c)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (matrix[++i])
	{
		while (matrix[i][++j])
		{
			if (matrix[i][j] == DOLLAR_MARKER && c == '$')
				matrix[i][j] = c;
			else if (matrix[i][j] == EXPANSION_MARKER && c == '*')
				matrix[i][j] = c;
			else if (matrix[i][j] == SINGLE_QUOTE_MARKER && c == '\'')
				matrix[i][j] = '\'';
			else if (matrix[i][j] == DOUBLE_QUOTE_MARKER && c == '\"')
				matrix[i][j] = '\"';
		}
		j = -1;
	}
}

bool	edge_case(t_wildcard *list, const char *wildcard)
{
	char	*card;

	card = NULL;
	if (count_char(wildcard, '*') == 2 && wildcard[0] == '*'
		&& wildcard[ft_strlen(wildcard) - 1] == '*')
	{
		card = ft_substr(wildcard, 1, ft_strlen(wildcard) - 2);
		if (ft_strstr(list->file_dir, card))
		{
			free(card);
			return (true);
		}
		else
		{
			free(card);
			list->match = false;
			return (true);
		}
	}
	if (card)
		free(card);
	return (false);
}

bool	is_hidden_file(char *str)
{
	return (strchr_index(str, '.') == 0);
}
