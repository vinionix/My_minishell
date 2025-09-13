#include "../consha.h"

int	count_chars_bs(char *str)
{
	int	i;
	int	size;

	i = -1;
	size = 0;
	while (str[++i])
	{
		if (str[i] != '\\')
			size++;
	}
	return (size);
}

static char	*dup_without_bslashs(char *str)
{
	char	*new_str;
	int		size;
	int		pos;
	int		i;

	if (!str)
		return (NULL);
	size = count_chars_bs(str);
	i = -1;
	pos = 0;
	new_str = (char *)ft_calloc(1, size + 1);
	i = 0;
	while (pos < size)
	{
		if (str[i] != '\\')
			new_str[pos++] = str[i];
		i++;
	}
	free(str);
	return (new_str);
}

void	remove_backslashs(char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
	{
		if (have_char(matrix[i], '\\'))
			matrix[i] = dup_without_bslashs(matrix[i]);
	}
}
