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

int	change_dir(char *str)
{
	if (chdir(str))
	{
		printf("minishell: cd: %s: No such file or directory\n", str);
		return (1);
	}
	return (0);
}

int	check_home(char *str)
{
	if (str[0] && str[0] == '~' && !str[1])
		return (1);
	if (str[0] && str[0] == '~' && str[1] && str[1] == '/')
		return (2);
	return (0);
}

static int	home_set(t_env *env_list, int home)
{
	if (!find_env("HOME=", env_list) && (home == 1 || home == 2))
	{
		printf("minishell: cd: HOME not set\n");
		return (0);
	}
	return (1);
}

int	parse_home(char **matrix, t_env *env_list)
{
	char	*temp;
	char	*home_path;
	int		home;

	home = check_home(*matrix);
	if (!home_set(env_list, home))
		return (1);
	if (home == 0)
		return (0);
	home_path = ft_strjoin(find_env("HOME=", env_list)->value, "/");
	if (home == 2)
	{
		temp = *matrix;
		*matrix = ft_strjoin(home_path, *matrix + 2);
		free(temp);
	}
	else if (home == 1)
	{
		temp = *matrix;
		*matrix = ft_strdup(find_env("HOME=", env_list)->value);
		free(temp);
	}
	free(home_path);
	return (0);
}
