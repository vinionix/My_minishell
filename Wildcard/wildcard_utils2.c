/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/06/12 16:12:33 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*update_vars(t_wildcard *list, const char *wildcard, t_var *var)
{
	char	*str;

	str = NULL;
	list->index += var->size - var->start;
	var->start = var->size + 1;
	if (var->start - 1 < (unsigned int)ft_strlen(wildcard))
		var->size = strchr_index_next(wildcard, '*', var->start);
	str = ft_substr(wildcard, var->start, var->size - var->start);
	return (str);
}

void	reset_asterisks(char **matrix)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (matrix[++i])
	{
		while (matrix[i][++j])
		{
			if (matrix[i][j] == WILDCARD_MARKER)
				matrix[i][j] = '*';
		}
		j = -1;
	}
}

char	**command_with_asterisk(char **matrix)
{
	char	**solo_matrix;

	solo_matrix = NULL;
	if (have_char(matrix[0], '*'))
	{
		solo_matrix = (char **)malloc(2 * sizeof(char *));
		solo_matrix[0] = ft_strdup(matrix[0]);
		solo_matrix[1] = NULL;
		free_matrix(matrix);
		return (solo_matrix);
	}
	return (matrix);
}

bool	is_hidden_file(char *str)
{
	return (strchr_index(str, '.') == 0);
}
