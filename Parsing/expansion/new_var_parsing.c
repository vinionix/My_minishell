/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_var_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:01:44 by vfidelis          #+#    #+#             */
/*   Updated: 2025/05/15 22:01:44 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

t_env	*find_env(const char *target_key, t_env *envs)
{
	size_t	equals_sign;

	equals_sign = (size_t)strchr_index(target_key, '=');
	while (envs)
	{
		if (!(ft_strncmp(target_key, (const char *)envs->key, equals_sign))
				&& ft_strlen((const char *)envs->key) == equals_sign)
			return (envs);
		envs = envs->next;
	}
	return (NULL);
}

int	change_env(const char *target_key, t_env *envs)
{
	t_env	*env_to_change;
	int		equals_sign;

	equals_sign = strchr_index(target_key, '=') + 1;
	env_to_change = find_env(target_key, envs);
	free(env_to_change->value);
	env_to_change->value = ft_strdup(target_key + equals_sign);
	return (0);
}

void	create_env(const char *str, t_env **envs)
{
	int		i;
	char	*key;
	char	*value;
	t_env	*new;

	value = NULL;
	new = NULL;
	i = strchr_index(str, '=');
	key = (char *)malloc(i + 1);
	if (!key)
		return ;
	key[i] = '\0';
	while (--i >= 0)
		key[i] = str[i];
	i = strchr_index(str, '=');
	i++;
	value = ft_strdup(str + i);
	new = export_new_env(key, value);
	envadd_back(envs, new);
}

static void	parse(char *variable, t_env **envs, int *return_value)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	if (check_first_char(variable))
	{
		*return_value = 1;
		return ;
	}
	while (variable[i] && variable[i] != '=')
	{
		if (check_following_chars(variable, variable[i++]))
		{
			flag = 1;
			*return_value = 1;
			break ;
		}
	}
	create_variable_if(variable, envs, &flag, return_value);
}

int	new_var_parsing(char **matrix, t_env **envs)
{
	int		i;
	int		return_value;

	i = 1;
	return_value = 0;
	while (matrix[i])
		parse(matrix[i++], envs, &return_value);
	return (return_value);
}
