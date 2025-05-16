/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:07:31 by gada-sil          #+#    #+#             */
/*   Updated: 2025/05/15 22:05:10 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*env_new(void)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = (NULL);
	new_node->value = (NULL);
	new_node->next = (NULL);
	return (new_node);
}

int	env_lstsize(t_env *lst)
{
	size_t	i;
	t_env	*temp;

	i = 0;
	if (lst == NULL)
		return (0);
	temp = lst;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

void	envadd_back(t_env **lst, t_env *new)
{
	t_env	*current;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

t_env	*export_new_env(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->next = (NULL);
	return (new_node);
}
