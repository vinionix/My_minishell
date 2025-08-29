/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 22:40:32 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/29 20:05:06 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	command_pipe_left(int *stdin_fd, t_tree *tree, t_process **process)
{
	t_process	*temp;
	int			pipe_temp[2];

	pipe(pipe_temp);
	process_add_back(process, node_process_creator(tree->left));
	temp = search_process(process, tree->left);
	if (temp->pid == 0)
	{
		verify_stdin(stdin_fd);
		dup2(pipe_temp[1], STDOUT_FILENO);
		close(pipe_temp[0]);
		close(pipe_temp[1]);
		exorcise(tree->left, *process);
	}
	else
	{
		if (*stdin_fd != -1)
			close(*stdin_fd);
		close(pipe_temp[1]);
		*stdin_fd = pipe_temp[0];
	}
}

static void	command_pipe_right(int *stdin_fd, t_tree *tree, t_process **process)
{
	int			pipe_temp[2];
	t_process	*temp;

	pipe(pipe_temp);
	process_add_back(process, node_process_creator(tree->right));
	temp = search_process(process, tree->right);
	if (temp->pid == 0)
	{
		verify_stdin(stdin_fd);
		if (tree->main != 1 && tree->prev->type == TK_PIPE
			&& get_data()->l_or_r == 1)
			dup2(pipe_temp[1], STDOUT_FILENO);
		close(pipe_temp[0]);
		close(pipe_temp[1]);
		exorcise(tree->right, *process);
	}
	else
	{
		if (*stdin_fd != -1)
			close(*stdin_fd);
		close(pipe_temp[1]);
		*stdin_fd = pipe_temp[0];
	}
}

static void	pipe_iteration(t_tree **tree, t_process **process, int *stdin_fd)
{
	if ((*tree)->left->type >= TK_REDIR_IN && (*tree)->left->type <= TK_APPEND)
		solo_redirect((*tree)->left, stdin_fd);
	else if ((*tree)->left->type == TK_COMMAND)
		command_pipe_left(stdin_fd, (*tree), process);
	if ((*tree)->right->type >= TK_REDIR_IN
		&& (*tree)->right->type <= TK_APPEND)
		solo_redirect((*tree)->right, stdin_fd);
	else if ((*tree)->right->type == TK_COMMAND)
		command_pipe_right(stdin_fd, (*tree), process);
	if ((*tree)->main == 1)
	{
		if (*stdin_fd != -1)
			close(*stdin_fd);
		*stdin_fd = -1;
	}
}

static void	aux_ft_pipe(t_tree **tree, int left_or_rigth,
	t_process **process, int *stdin_fd)
{
	while ((*tree)->type == TK_PIPE)
	{
		if (left_or_rigth == 1)
		{
			get_data()->l_or_r = 1;
			pipe_iteration(tree, process, stdin_fd);
			if ((*tree)->main == 1)
				break ;
			(*tree) = (*tree)->prev;
		}
		if (left_or_rigth == 0)
		{
			get_data()->l_or_r = 0;
			pipe_iteration(tree, process, stdin_fd);
			(*tree) = (*tree)->right;
		}
	}
	if (*stdin_fd != -1)
		close(*stdin_fd);
}

void	ft_pipe(t_tree **tree, int left_or_rigth)
{
	int			stdin_fd;
	t_tree		*current;
	t_process	*process;

	current = (*tree);
	process = NULL;
	stdin_fd = -1;
	if (left_or_rigth == 1)
	{
		get_data()->l_or_r = 1;
		pipe_iteration(tree, &process, &stdin_fd);
		if ((*tree)->main != 1)
			(*tree) = (*tree)->prev;
	}
	if (stdin_fd == -1 && left_or_rigth == 1)
	{
		if (process)
			wait_free_process(&process);
		return ;
	}
	aux_ft_pipe(tree, left_or_rigth, &process, &stdin_fd);
	if (left_or_rigth == 0)
		(*tree) = current;
	if (process)
		wait_free_process(&process);
}
