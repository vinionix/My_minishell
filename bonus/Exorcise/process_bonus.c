/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 01:43:49 by gada-sil          #+#    #+#             */
/*   Updated: 2025/08/27 15:46:03 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

t_process	*node_process_creator(t_tree *node)
{
	t_process	*node_process;

	node_process = (t_process *)malloc(sizeof(t_process));
	node_process->prev = NULL;
	node_process->next = NULL;
	node_process->pid = -1;
	node_process->id_tree = node->id_tree;
	return (node_process);
}

void	process_add_back(t_process **main, t_process *node)
{
	t_process	*temp;

	temp = (*main);
	if ((*main) == NULL)
	{
		*main = node;
		return ;
	}
	while ((*main)->next != NULL)
		*main = (*main)->next;
	node->prev = *main;
	(*main)->next = node;
	*main = temp;
}
