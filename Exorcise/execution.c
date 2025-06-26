/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:57:58 by vfidelis          #+#    #+#             */
/*   Updated: 2025/06/26 06:05:55 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

int	exit_status = 0;

t_tree	*last_left(t_tree *tree)
{
    while (tree->left && tree->left->type != TK_COMMAND)
		tree = tree->left;
	return (tree);
}

static t_process	*node_process_creator(t_tree *node_tree)
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
	t_process	*temp;

	temp = (*main);
	if ((*main) == NULL)
	{
		*main = node;
		return ;
	}
	while ((*main)->next != NULL)
		*main = (*main)->next;
	(*main)->next = node;
	node->prev = *main;
	*main = temp;
}
void	exorcise(t_tree **tree, t_process **process, t_tree *current_node)
{
	t_process	*temp;
	int			status;

	process_add_back(process, node_process_creator(current_node));
	temp = (*process);
	while ((*process)->next && (*process)->id_tree != current_node->id_tree)
		(*process) = (*process)->next;
	if ((*process)->pid)
	{
		waitpid((*process)->pid, &status, 0);
		exit_status = WEXITSTATUS(status);
		if (exit_status == 0)
			(*tree)->u_define.operators.result1 = 0;
		printf ("%d\n", (*tree)->u_define.operators.result1);
	}
	else
	{
		execve("/bin/ls", current_node->u_define.command.cmd, NULL);
		exit(1);
	}
	(*process) = temp;
}

void	process_creator(t_tree **tree, t_process **process)
{
	t_tree	*current_node;
	int			status;

	status = 0;
	current_node = last_left((*tree));
	if (current_node->type == TK_OR)
	{
		if (current_node->left->type == TK_OR)
		{
			if (current_node->left->u_define.operators.valid == -1)
			{
				current_node->u_define.operators.valid = -1;
				current_node = current_node->prev;
			}
		}
		if (current_node->left->type == TK_COMMAND)
			exorcise(tree, process, current_node->left);
		if (current_node->right->type == TK_COMMAND && current_node->u_define.operators.result1 == -1)
		{
			printf("oi");
			exorcise(tree, process, current_node->right);
		}
	}
}
