/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cd_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/27 15:50:44 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard_bonus.h"

static void	replace_asterisk(t_wildcard *list)
{
	int	i;

	i = -1;
	while (list)
	{
		while (list->file_dir[++i])
		{
			if (list->file_dir[i] == '*')
				list->file_dir[i] = EXPANSION_MARKER;
		}
		i = -1;
		list = list->next;
	}
}

int	read_current_dir(t_wildcard **list)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*temp;

	dir = opendir(".");
	temp = NULL;
	if (dir == NULL)
	{
		perror("opendir");
		return (1);
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		temp = ft_strdup((const char *)entry->d_name);
		wild_addback(list, wild_lstnew(temp));
		temp = NULL;
		entry = readdir(dir);
	}
	replace_asterisk(*list);
	closedir(dir);
	return (0);
}
