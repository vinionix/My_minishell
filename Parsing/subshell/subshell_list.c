/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:36:34 by gada-sil          #+#    #+#             */
/*   Updated: 2025/08/20 16:56:07 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_subshell  *subshell_new(t_token *tokens)
{
    t_subshell	*new_node;

	new_node = (t_subshell *)malloc(sizeof(t_subshell));
	if (!new_node)
		return (NULL);
	tree_creator(&tokens, &new_node->tree, -1);
	new_node->next = (NULL);
    new_node->prev = (NULL);
	return (new_node);
}

void	subshelladd_back(t_subshell **lst, t_subshell *new)
{
	t_subshell	*current;

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