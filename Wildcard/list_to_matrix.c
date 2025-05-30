/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/05/16 04:06:53 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_wildlist(t_wildcard **list)
{
	t_wildcard *temp;

	temp = *list;
	while (*list)
	{
		temp = (*list)->next;
		if (!(*list)->match)
		{
			free((char *)(*list)->fileOrDir);
			free(*list);
		}
		else
			free((*list));
		*list = temp;
	}
}

static int	wild_matches_size(t_wildcard *list)
{
	int	i;

	i = 0;
	while (list)
	{
		if (list->match)
			i++;
		list = list->next;
	}
	return (i);
}

const char	**list_to_matrix(t_wildcard *list)
{
	const char		**matrix;
	int			size;
	t_wildcard	*temp;

	matrix = NULL;
	size = wild_matches_size(list);
	if (size == 0)
		return (NULL);
	matrix = (const char **)malloc((size + 1) * sizeof(char *));
	if (!matrix)
		return (NULL);
	temp = list;
	matrix[size] = NULL;
	while (temp)
	{
		if (temp->match)
			matrix[--size] = temp->fileOrDir;
		temp = temp->next;
	}
	return (matrix);
}
