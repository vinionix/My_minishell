/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:12:24 by vfidelis          #+#    #+#             */
/*   Updated: 2025/07/15 04:13:03 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_strjoin_pipex(char const *s1, char const *s2)
{
	char	*receptor;
	size_t	len;
	size_t	i;
	size_t	j;

	j = 0;
	i = -1;
	len = ft_strlen(s1) + ft_strlen(s2);
	while (s2[j] == ' ' || s2[j] == '\t')
		j++;
	if (s1 == NULL || s2 == NULL || s2[j] == '\0')
		return (NULL);
	receptor = (char *)malloc(sizeof(char) * (len + 2));
	while (s1[++i] != '\0')
		receptor[i] = s1[i];
	if (s2[j] != '/')
		receptor[i++] = '/';
	while (s2[j] != '\0')
	{
		receptor[i++] = s2[j++];
		if (s2[j] == ' ' || s2[j] == '\t')
			break ;
	}
	receptor[i] = '\0';
	return (receptor);
}

char	**get_path(t_env *env)
{
	char	**path;
    t_env   *temp;

    temp = find_env("PATH=", env);
	path = NULL;
	path = ft_split(temp->value, ':');
	return (path);
}

static int	ft_strcmp_path(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s2[i])
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	if (s2[i] == '\0' || (s2[i] == '/' && s2[i + 1] == '\0'))
		return (0);
	return (-1);
}

static int	aux_valid_path(char **path, char **cmd)
{
	int		j;

	j = 0;
	while (path[j])
	{
		if (ft_strcmp_path(path[j], cmd[0]) == 0)
			break ;
		j++;
	}
	if (access(cmd[0], X_OK | F_OK) == 0)
		return (0);
	return (-1);
}

int	valid_path(char **cmd, char **path)
{
	int		j;
	char	*str;

	str = NULL;
	j = 0;
	if (aux_valid_path(path, cmd) == 0)
		return (0);
	while (path[j])
	{
		str = ft_strjoin_pipex(path[j], cmd[0]);
		if (str != NULL)
        {
            if (access(str, X_OK | F_OK) == 0)
			{
				free(cmd[0]);
				cmd[0] = str;
            	return (0);
			}
            free(str);
        }
		j++;
	}
	return (-1);
}
