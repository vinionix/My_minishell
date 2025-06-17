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
	closedir(dir);
	return (0);
}
