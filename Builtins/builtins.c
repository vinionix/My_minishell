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

int	built_cd(const char **matrix)
{
	int	return_value;

	return_value = 0;
	if (ft_len_matrix((char **)matrix) > 1)
	{
		printf("Too many args for cd command\n");
		return_value = 1;
	}
	else if (!ft_strcmp(*matrix, "~") || !ft_strcmp(*matrix, "~/")
		|| *matrix == NULL)
	{
		if (chdir("/home"))
			return_value = 1;
	}
	else if (chdir(*matrix))
		return_value = 1;
	free_matrix((char **)matrix);
	return (return_value);
}

int	built_echo_n(const char **matrix)
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
	free_matrix((char **)matrix);
	return (0);
}

int	built_echo(const char **matrix)
{
	int	i;

	i = -1;
	while (matrix[i + 2] != NULL)
	{
		printf("%s ", matrix[++i]);
	}
	printf("%s\n", matrix[i]);
	free_matrix((char **)matrix);
	return (0);
}

static	const char *get_pwd(void)
{
	const char	*pwd;
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

int	built_pwd(const char **matrix)
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
	{
		if (matrix)
			free_matrix((char **)matrix);
		return (1);
	}
	printf("%s\n", pwd);
	free((char *)pwd);
	if (matrix)
		free_matrix((char **)matrix);
	return (0);
}
