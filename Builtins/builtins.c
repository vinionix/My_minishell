/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 01:43:41 by gada-sil          #+#    #+#             */
/*   Updated: 2025/05/15 22:17:31 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(char **matrix, t_env *env_list)
{
	int		return_value;

	return_value = 0;
	if (!matrix)
		return (1);
	if (ft_len_matrix((char **)matrix) > 1)
	{
		printf("Too many args for cd command\n");
		return_value = 1;
	}
	else if (!ft_strcmp(*matrix, "~") || !ft_strcmp(*matrix, "~/"))
	{
		if (chdir(find_env("HOME=", env_list)->value))
			return_value = 1;
	}
	else if (chdir(*matrix))
		return_value = 1;
	if (return_value == 0)
		change_cwd(env_list);
	return (return_value);
}

int	ft_echo_n(const char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		if (matrix[i + 1] != NULL)
			printf("%s ", matrix[i++]);
		else
			printf("%s", matrix[i++]);
	}
	return (0);
}

int	ft_echo(const char **matrix)
{
	int	i;

	i = -1;
	while (matrix[i + 2] != NULL)
	{
		printf("%s ", matrix[++i]);
	}
	printf("%s\n", matrix[i]);
	return (0);
}

int	ft_pwd(const char **matrix)
{
	const char	*pwd;
	int		flag;

	flag = check_flag(matrix);
	if (flag)
	{
		printf("minishell: pwd: %c%c: invalid option\n", (*matrix)[0], (*matrix)[1]);
		free_matrix((char **)matrix);
		return (2);
	}
	pwd = get_pwd();
	if (!pwd)
		return (1);
	printf("%s\n", pwd);
	free((char *)pwd);
	return (0);
}

int	ft_export(char **matrix, t_env **envs)
{
	return (new_var_parsing(matrix, envs));
}
