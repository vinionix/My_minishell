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

int	check_flag(const char **matrix)
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
