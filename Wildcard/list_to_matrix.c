/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/06/12 16:12:32 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	free_wildlist(t_wildcard **list)
{
	t_wildcard	*temp;

	temp = *list;
	while (*list)
	{
		temp = (*list)->next;
		free((char *)(*list)->file_dir);
		free(*list);
		*list = temp;
	}
}

static int	wild_matches_size(t_wildcard *list, bool show_hidden)
{
	int	i;

	i = 0;
	if (show_hidden)
	{
		while (list)
		{
			if (list->match)
				i++;
			list = list->next;
		}
	}
	else
	{
		while (list)
		{
			if (list->match && !list->is_hidden)
				i++;
			list = list->next;
		}
	}
	return (i);
}

static void	dup_into_matrix(t_wildcard *temp, char **matrix,
			bool show_hidden, int size)
{
	if (show_hidden)
	{
		while (temp)
		{
			if (temp->match)
				matrix[--size] = ft_strdup(temp->file_dir);
			temp = temp->next;
		}
	}
	else
	{
		while (temp)
		{
			if (temp->match && !temp->is_hidden)
				matrix[--size] = ft_strdup(temp->file_dir);
			temp = temp->next;
		}
	}
}

char	**list_to_matrix(t_wildcard *list, bool show_hidden)
{
	char		**matrix;
	int			size;

	matrix = NULL;
	size = wild_matches_size(list, show_hidden);
	if (size == 0)
		return (NULL);
	matrix = (char **)malloc((size + 1) * sizeof(char *));
	if (!matrix)
		return (NULL);
	matrix[size] = NULL;
	dup_into_matrix(list, matrix, show_hidden, size);
	return (matrix);
}
