/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 01:43:49 by gada-sil          #+#    #+#             */
/*   Updated: 2025/05/15 22:18:08 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_env_if(t_env **envs, const char *target_key)
{
	t_env	*temp;
	int		equals_sign;

	if (!*envs || !envs)
		return ;
	temp = *envs;
	equals_sign = strchr_index(target_key, '=');
	if (!(ft_strncmp(target_key, (const char *)(*envs)->key, equals_sign)))
	{
		*envs = temp->next;
		free(temp);
		unset_env_if(envs, target_key);
	}
	else
	{
		temp = *envs;
		unset_env_if(&temp->next, target_key);
	}
}

int	built_env(t_env *env)
{
	t_env	*temp;

	temp = env;
	if (!env)
		return (1);
	while (temp)
	{
		printf("%s", temp->key);
		printf("=");
		printf("%s\n", temp->value);
		temp = temp->next;
	}
	return (0);
}
