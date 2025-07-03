/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 01:43:41 by gada-sil          #+#    #+#             */
/*   Updated: 2025/05/15 22:17:31 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_cwd(t_env *env_list)
{
	t_env	*env_to_change;

	env_to_change = find_env("PWD=", env_list);
	free(env_to_change->value);
	env_to_change->value = get_pwd();
}

int	check_flag(char **matrix)
{
	if (matrix)
	{
		if (*matrix)
		{
			if ((*matrix)[0] == '-' && (*matrix)[1] != '\0')
				return (1);
		}
	}
	return (0);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

char	*get_pwd(void)
{
	char	*pwd;
	size_t		size;

	pwd = NULL;
	size = 128;
	while (42)
	{
		pwd = (char *)malloc(size);
		if (!pwd)
		{
			perror("malloc");
			return (NULL);
		}
		if (getcwd((char *)pwd, size) != NULL)
			return (pwd);
		free((char *)pwd);
		if (errno != ERANGE)
		{
			perror("getcwd");
			return (NULL);
		}
		size *= 2;
	}
	return (pwd);
}
