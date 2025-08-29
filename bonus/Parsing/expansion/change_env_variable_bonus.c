/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_variable_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:43:40 by gada-sil          #+#    #+#             */
/*   Updated: 2025/08/28 14:51:50 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_bonus.h"

void	change_var(t_env *envs, char *env_to_change, char *value)
{
	t_env	*env;

	env = find_env(env_to_change, envs);
	free(env->value);
	env->value = ft_strdup(value);
	free(value);
}

void	create_default_env(t_env **envs)
{
	char	*pid_str;
	char	*pid_var;

	pid_str = ft_strdup("424242");
	pid_var = ft_strjoin("$=", pid_str);
	create_env(pid_var, envs);
	create_env("?=0", envs);
	free(pid_str);
	free(pid_var);
}
