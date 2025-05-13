/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 01:43:49 by gada-sil          #+#    #+#             */
/*   Updated: 2025/05/02 05:11:29 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_env(t_env **env, const char *new_env)
{
  (void)env;
  (void)new_env;
  return (0);
}

void  unset_env_if(t_env **envs, const char *target_key)
{
	t_env	*temp;
  int   equals_sign;

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

int built_env(t_env *env)
{
  t_env *temp;
  
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
