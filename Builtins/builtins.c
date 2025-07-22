/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
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

int	ft_cd(char **matrix, t_env *env_list)
{
	int		home;

	if (!matrix)
		return (1);
	if (ft_len_matrix(matrix) > 2)
	{
		printf("Too many args for cd command\n");
		return (1);
	}
	else if (ft_len_matrix(matrix) == 1)
	{
		if (chdir(find_env("HOME=", env_list)->value))
			return (1);
		change_cwd(env_list);
		return (0);
	}
	home = check_home(*(++matrix));
	parse_home(matrix, home, env_list);
	if (chdir(*matrix))
		return (1);
	change_cwd(env_list);
	return (0);
}

int	ft_echo_n(char **matrix)
{
	int	i;

	i = 1;
	if (matrix[i])
	{
		while (matrix[i])
		{
			if (matrix[i + 1] != NULL)
				printf("%s ", matrix[i]);
			else
				printf("%s", matrix[i]);
			i++;
		}
	}
	else
		printf("\n");
	return (0);
}

int	ft_echo(char **matrix)
{
	int	i;

	i = 1;
	if (matrix[i] != NULL)
	{
		while (matrix[i] != NULL)
		{
			if (matrix[i + 1] == NULL)
				printf("%s\n", matrix[i]);
			else
				printf("%s ", matrix[i]);
			i++;
		}
	}
	else
		printf("\n");
	return (0);
}

int	ft_pwd(char **matrix)
{
	char	*pwd;
	int		flag;

	flag = check_flag(matrix);
	if (flag)
	{
		printf("minishell: pwd: %c%c: invalid option\n", (*matrix)[0], (*matrix)[1]);
		free_matrix(matrix);
		return (2);
	}
	pwd = get_pwd();
	if (!pwd)
		return (1);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

int	ft_export(char **matrix, t_env **envs)
{
	return (new_var_parsing(matrix, envs));
}
