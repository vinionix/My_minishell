/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:07:31 by gada-sil          #+#    #+#             */
/*   Updated: 2025/08/12 22:27:32 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int	find_size(char *copy)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (copy[i])
	{
		if (copy[i++] == '$')
			size++;
	}
	i = 0;
	while (copy[i++])
	{
		if (copy[i] == '$' && copy[i + 1] == '$')
		{
			size--;
			i++;
		}
	}
	return (size);
}

void	fix_pid_and_status(int *i, char **matrix, int *j, char *str)
{
	if (str[*i + 1] == '$')
		matrix[(*j)++] = ft_strdup("$$");
	else
		matrix[(*j)++] = ft_strdup("$?");
	*i += 2;
	*i = jump_to(str, '$', *i);
}

void	parse_edge_case(char **matrix)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (matrix[++i])
	{
		while (matrix[i][++j])
		{
			if (matrix[i][j] == '$' && matrix[i][j + 1] == '$')
			{
				j++;
				continue ;
			}
			if (matrix[i][j] == '$' && (matrix[i][j + 1] == ' '
				|| matrix[i][j + 1] == SINGLE_QUOTE_MARKER
				|| matrix[i][j + 1] == '\0' || matrix[i][j + 1] == '\"'
				|| matrix[i][j + 1] == '+' || matrix[i][j + 1] == '%'))
				matrix[i][j] = DOLLAR_MARKER;
			if (matrix[i][j] == '$' && matrix[i][j + 1] == '*')
				matrix[i][j + 1] = '1';
		}
		j = -1;
	}
}

void	create_envs(char *copy, char *str, int i, char **matrix)
{
	int	j;
	int	size;

	j = 0;
	size = 0;
	while (copy[i])
	{
		if (!copy[i])
			break ;
		if (str[i + 1] == '$' || str[i + 1] == '?')
		{
			fix_pid_and_status(&i, matrix, &j, str);
			continue ;
		}
		size = i + 1;
		if (copy[size] == EXPANSION_MARKER)
		{
			i++;
			continue ;
		}
		while (copy[size] == POSSIBLE_ENV_MARKER)
			size++;
		matrix[j++] = ft_substr(str, i, size - i);
		i = jump_to(copy, '$', i + 1);
	}
}

char	*mark_expansions(char *str)
{
	int		i;
	char	*copy;

	i = jump_to(str, '$', 0);
	copy = ft_strdup((const char *)str);
	while (copy[i])
	{
		i++;
		if (copy[i] == '?' || copy[i] == '$')
		{
			copy[i] = POSSIBLE_ENV_MARKER;
			i++;
			i = jump_to(copy, '$', i);
			continue ;
		}
		while (check_meta(copy[i]))
			copy[i++] = POSSIBLE_ENV_MARKER;
		i = jump_to(copy, '$', i);
	}
	return (copy);
}
