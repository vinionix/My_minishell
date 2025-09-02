#include "wildcard.h"

int	count_chars(char *str)
{
	int	i;
	int	size;

	i = -1;
	size = 0;
	while (str[++i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			size++;
	}
	return (size);
}

static char	*dup_without_quotes(char *str)
{
	char	*new_str;
	int		size;
	int		pos;
	int		i;

	new_str = NULL;
	size = count_chars(str);
	i = -1;
	pos = 0;
	new_str = (char *)ft_calloc(1, size + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (pos < size)
	{
		if (str[i] != '\'' && str[i] != '\"')
			new_str[pos++] = str[i];
		i++;
	}
	free(str);
	return (new_str);
}

void	remove_quotes(char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
	{
		if (have_char(matrix[i], '\'') || have_char(matrix[i], '\"'))
			matrix[i] = dup_without_quotes(matrix[i]);
	}
}
