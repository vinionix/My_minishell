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

int	built_cd(const char *str)
{
	if (!ft_strcmp(str, "~") || !ft_strcmp(str, "~/")
		|| str == NULL)
	{
		if (chdir("/home"))
			return (1);
		return (0);
	}
	if (chdir(str))
		return (1);
	return (0);
}

int	built_echo_n(const char *str)
{
	printf("%s", str);
	return (0);
}

int	built_echo(const char *str)
{
	printf("%s\n", str);
	return (0);
}

char	*built_pwd(void)
{
	char	*pwd;
	size_t	size;

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
		if (getcwd(pwd, size) != NULL)
			return (pwd);
		free(pwd);
		if (errno != ERANGE)
		{
			perror("getcwd");
			return (NULL);
		}
		size *= 2;
	}
}
