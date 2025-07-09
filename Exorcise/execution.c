/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:57:58 by vfidelis          #+#    #+#             */
/*   Updated: 2025/07/06 16:40:33 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			exit_status = -1;

t_tree	*last_left(t_tree *tree)
{
	while (tree->left && tree->left->type != TK_COMMAND)
		tree = tree->left;
	return (tree);
}

t_process	*node_process_creator(t_tree *node)
{
	t_process	*node_process;

	node_process = malloc(sizeof(t_process));
	node_process->prev = NULL;
	node_process->next = NULL;
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
void	exorcise(t_tree *current_node, int flag)
{
	if (flag == 0)
	{
		if (current_node->prev && current_node->prev->type == TK_PIPE)
		{
			dup2(current_node->prev->u_define.pipe.pipefd[1], STDOUT_FILENO);
			close(current_node->prev->u_define.pipe.pipefd[0]);
			close(current_node->prev->u_define.pipe.pipefd[1]);
		}
	}
	else if (flag == 1)
	{
		if (current_node->prev->prev
			&& current_node->prev->prev->type == TK_PIPE)
		{
			dup2(current_node->prev->prev->u_define.pipe.pipefd[1],
				STDOUT_FILENO);
			close(current_node->prev->prev->u_define.pipe.pipefd[0]);
			close(current_node->prev->prev->u_define.pipe.pipefd[1]);
		}
	}
	else if (flag == 2)
	{
		if (current_node->prev->right
			&& current_node->prev->right->type == TK_PIPE)
		{
			dup2(current_node->prev->right->u_define.pipe.pipefd[1],
				STDOUT_FILENO);
			close(current_node->prev->right->u_define.pipe.pipefd[0]);
			close(current_node->prev->right->u_define.pipe.pipefd[1]);
		}
	}
	execve(current_node->u_define.command.cmd[0], current_node->u_define.command.cmd, NULL);
	exit(1);
}

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

void	tk_or(t_tree **current_node)
{
	pid_t	pid;
	int		status;

	if ((*current_node)->left->type == TK_COMMAND)
	{
		pid = fork();
		if (pid == 0)
			exorcise((*current_node)->left, -1);
		else
		{
			waitpid(pid, &status, 0);
			get_data()->exit_code = WEXITSTATUS(status);
		}
	}
	if ((*current_node)->right->type == TK_PIPE && get_data()->exit_code != 0)
		tk_pipe_right((*current_node)->right);
	else if ((*current_node)->right->type == TK_COMMAND
		&& get_data()->exit_code != 0)
	{
		pid = fork();
		if (pid == 0)
			exorcise((*current_node)->right, -1);
		else
		{
			waitpid(pid, &status, 0);
			get_data()->exit_code = WEXITSTATUS(status);
		}
	}
}

void	tk_and(t_tree **current_node)
{
	pid_t	pid;
	int		status;

	if ((*current_node)->left->type == TK_COMMAND)
	{
		pid = fork();
		if (pid == 0)
			exorcise((*current_node)->left, -1);
		else
		{
			waitpid(pid, &status, 0);
			get_data()->exit_code = WEXITSTATUS(status);
		}
	}
	if ((*current_node)->right->type == TK_PIPE && get_data()->exit_code == 0)
		tk_pipe_right((*current_node)->right);
	else if ((*current_node)->right->type == TK_COMMAND
		&& get_data()->exit_code == 0)
	{
		pid = fork();
		if (pid == 0)
			exorcise((*current_node)->right, -1);
		else
		{
			waitpid(pid, &status, 0);
			get_data()->exit_code = WEXITSTATUS(status);
		}
	}
}
void	exorcise_manager(t_tree **tree)
{
	t_tree		*current_node;
	t_process	*process;
	int			saved_stdin;

	get_data()->exit_code = -1;
	process = NULL;
	current_node = last_left((*tree));
	if (current_node->main == 1)
	{
		if (current_node->type == TK_AND && (get_data()->exit_code == 0
				|| get_data()->exit_code == -1))
			tk_and(&current_node);
		else if (current_node->type == TK_OR && get_data()->exit_code != 0)
			tk_or(&current_node);
		if (current_node->type == TK_PIPE)
			tk_pipe_right(current_node);
		return ;
	}
	while (current_node)
	{
		if (current_node->type == TK_AND && (get_data()->exit_code == 0
				|| get_data()->exit_code == -1))
		{
			if (process)
				wait_free_processs(&process, saved_stdin);
			tk_and(&current_node);
		}
		else if (current_node->type == TK_OR && get_data()->exit_code != 0)
		{
			if (process)
				wait_free_processs(&process, saved_stdin);
			tk_or(&current_node);
		}
		if (current_node->type == TK_PIPE)
		{
			saved_stdin = dup(STDIN_FILENO);
			tk_pipe_left(&current_node, &process);
		}
		current_node = current_node->prev;
	}
	if (process)
		wait_free_processs(&process, saved_stdin);
	//printf("\nsaida = %d\n", get_data()->exit_code);
}
