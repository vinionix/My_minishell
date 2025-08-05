/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 01:43:41 by gada-sil          #+#    #+#             */
/*   Updated: 2025/07/22 17:40:46 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_home(char *str)
{
	if (str[0] && str[0] == '~' && !str[1])
		return (1);
	if (str[0] && str[0] == '~' && str[1] && str[1] == '/')
		return (2);
	return (0);
}

void	parse_home(char **matrix, int home, t_env *env_list)
{
	char	*temp;
	char	*home_path;

	temp = NULL;
	home_path = ft_strjoin(find_env("HOME=", env_list)->value, "/");
	if (home == 2)
	{
		temp = *matrix;
		*matrix = ft_strjoin(home_path, *matrix + 2);
		free(temp);
		free(home_path);
	}
	else if (home == 1)
	{
		temp = *matrix;
		*matrix = ft_strdup(find_env("HOME=", env_list)->value);
		free(temp);
	}
}
