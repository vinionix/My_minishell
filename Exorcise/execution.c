/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:57:58 by vfidelis          #+#    #+#             */
/*   Updated: 2025/06/18 15:25:11 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

t_tree	*last_left(t_tree *tree)
{
    while (tree->left && tree->left != TK_COMMAND)
		tree = tree->left;
	return (tree);
}

static t_process	*node_process_creator(t_tree *node_tree)
{
	t_process	*node_process;

	node_process = malloc(sizeof(t_process));
	node_process->prev = NULL:
	node_process->next = NULL;
	node_process->id_tree = node_tree->id_tree;
	node_process->dad = node_tree->prev;
	node_process->pid = fork();
	return (node_process);
}
static void	process_add_back(t_process **main, t_process *node)
{
	 
}

t_process	*process_creator(t_tree **tree)
{
	t_tree		*last_node_left;
	t_process	*process;

	last_node_left = last_left((*tree));
	while (last_node_left->main != 1)
	{
		if (last_node_left->type == TK)
		{
			
		}
	}
}