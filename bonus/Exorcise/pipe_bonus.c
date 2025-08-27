/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 22:40:32 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/27 15:45:59 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

t_process	*search_process(t_process **process, t_tree *current_node)
{
	t_process	*temp;

	temp = (*process);
	while (temp->id_tree != current_node->id_tree)
		temp = temp->next;
	temp->pid = fork();
	return (temp);
}

void	wait_free_process(t_process **process)
{
	t_process	*temp;
	int			status;

	temp = (*process);
	while (temp != NULL)
	{
		waitpid(temp->pid, &status, 0);
		handle_sigint_in_fork(status, temp->pid);
		get_data()->exit_code = WEXITSTATUS(status);
		temp = temp->next;
	}
	temp = *process;
	while (temp)
	{
		temp = (*process)->next;
		free(*process);
		(*process) = temp;
	}
	change_env_var(get_data()->env, "?=", ft_itoa(get_data()->exit_code));
}

void	solo_redirect(t_tree *tree, int *stdin_fd)
{
	if (*stdin_fd != -1)
	{
		close(*stdin_fd);
		*stdin_fd = -1;
	}
	creat_solo_redirect(tree->u_define.command.list_redir);
}

void	first_iteration(t_tree **tree, t_process **process, int *stdin_fd,
		int l_or_r)
{
	int			pipe_temp[2];
	t_process	*temp;
	int			std_out;

	std_out = dup(1);
	if ((*tree)->left->type >= TK_REDIR_IN && (*tree)->left->type <= TK_APPEND)
		solo_redirect((*tree)->left, stdin_fd);
	else if ((*tree)->left->type == TK_COMMAND)
	{
		pipe(pipe_temp);
		process_add_back(process, node_process_creator((*tree)->left));
		temp = search_process(process, (*tree)->left);
		if (temp->pid == 0)
		{
			if (*stdin_fd != -1)
			{
				dup2(*stdin_fd, STDIN_FILENO);
				close(*stdin_fd);
			}
			dup2(pipe_temp[1], STDOUT_FILENO);
			close(pipe_temp[0]);
			close(pipe_temp[1]);
			exorcise((*tree)->left, std_out);
		}
		else
		{
			if (*stdin_fd != -1)
				close(*stdin_fd);
			close(pipe_temp[1]);
			*stdin_fd = pipe_temp[0];
		}
	}
	if ((*tree)->right->type >= TK_REDIR_IN
		&& (*tree)->right->type <= TK_APPEND)
		solo_redirect((*tree)->right, stdin_fd);
	else if ((*tree)->right->type == TK_COMMAND)
	{
		pipe(pipe_temp);
		process_add_back(process, node_process_creator((*tree)->right));
		temp = search_process(process, (*tree)->right);
		if (temp->pid == 0)
		{
			if (*stdin_fd != -1)
			{
				dup2(*stdin_fd, STDIN_FILENO);
				close(*stdin_fd);
			}
			if ((*tree)->main != 1 && (*tree)->prev->type == TK_PIPE
				&& l_or_r == 1)
				dup2(pipe_temp[1], STDOUT_FILENO);
			close(pipe_temp[0]);
			close(pipe_temp[1]);
			exorcise((*tree)->right, std_out);
		}
		else
		{
			if (*stdin_fd != -1)
				close(*stdin_fd);
			close(pipe_temp[1]);
			*stdin_fd = pipe_temp[0];
		}
	}
	if ((*tree)->main == 1)
	{
		if (*stdin_fd != -1)
			close(*stdin_fd);
		*stdin_fd = -1;
	}
	close(std_out);
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
		first_iteration(tree, &process, &stdin_fd, 1);
		if ((*tree)->main != 1)
			(*tree) = (*tree)->prev;
	}
	if (stdin_fd == -1 && left_or_rigth == 1)
	{
		if (process)
			wait_free_process(&process);
		return ;
	}
	while ((*tree)->type == TK_PIPE)
	{
		if (left_or_rigth == 1)
		{
			first_iteration(tree, &process, &stdin_fd, 1);
			if ((*tree)->main == 1)
				break ;
			(*tree) = (*tree)->prev;
		}
		if (left_or_rigth == 0)
		{
			first_iteration(tree, &process, &stdin_fd, 0);
			(*tree) = (*tree)->right;
		}
	}
	if (left_or_rigth == 0)
		(*tree) = current;
	if (process)
		wait_free_process(&process);
}
