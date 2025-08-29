/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:18:41 by gada-sil          #+#    #+#             */
/*   Updated: 2025/08/28 15:03:06 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_chars(char *str)
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
			else if (matrix[i][j] == SINGLE_QUOTE_MARKER && c == '\'')
				matrix[i][j] = '\'';
			else if (matrix[i][j] == DOUBLE_QUOTE_MARKER && c == '\"')
				matrix[i][j] = '\"';
		}
		j = -1;
	}
}
