/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:57:58 by vfidelis          #+#    #+#             */
/*   Updated: 2025/06/19 21:41:03 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

t_tree	*last_left(t_tree *tree)
{
    while (tree->left && tree->left->type != TK_COMMAND)
		tree = tree->left;
	return (tree);
}

/*static t_process	*node_process_creator(t_tree *node_tree)
{
	t_process	*node_process;

	node_process = malloc(sizeof(t_process));
	node_process->prev = NULL;
	node_process->next = NULL;
	node_process->id_tree = node_tree->id_tree;
	node_process->dad = node_tree->prev;
	node_process->pid = fork();
	return (node_process);
}
static void	process_add_back(t_process **main, t_process *node)
{
	 
}

void	*process_creator(t_tree **tree, t_process **process)
{
	t_tree	*current_node;
	int		flag;

	if (*process == NULL)
		current_node = last_left((*tree));
	if ((*tree)->main != 1)
	{
		if (current_node->main == 1)
		if (current_node->type >= TK)
	}
}*/