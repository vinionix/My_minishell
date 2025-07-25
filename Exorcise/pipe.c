/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 22:40:32 by vfidelis          #+#    #+#             */
/*   Updated: 2025/07/25 17:48:24 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		get_data()->exit_code  = WEXITSTATUS(status);
		temp = temp->next;
	}
	while ((*process))
	{
		temp = (*process);
		(*process) = (*process)->next;
		free(temp);
	}
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

void	pipe_for_command(t_tree **tree, int *stdin_fd, t_process **process)
{
	t_process	*temp;
	
	pipe((*tree)->prev->u_define.pipe.pipefd);
	process_add_back(process, node_process_creator((*tree)));
	temp = search_process(process, (*tree));
	if (temp->pid == 0)
	{
		if (*stdin_fd != -1)
		{
			dup2(*stdin_fd, STDIN_FILENO);
			close(*stdin_fd);
		}
		dup2((*tree)->prev->u_define.pipe.pipefd[1], STDOUT_FILENO);
		close((*tree)->prev->u_define.pipe.pipefd[1]);
		close((*tree)->prev->u_define.pipe.pipefd[0]);
		exorcise((*tree), -1);
	}
	else
	{
		if (*stdin_fd != -1)
			close(*stdin_fd);
		close((*tree)->prev->u_define.pipe.pipefd[1]);
		*stdin_fd = (*tree)->prev->u_define.pipe.pipefd[0];
	}
}

void	pipe_iteration(t_tree **tree, int *stdin_fd, t_process **process)
{
	if ((*tree)->left->type >= TK_FILE_IN && (*tree)->left->type <= TK_APPEND)
		solo_redirect((*tree)->left, stdin_fd);
	else if ((*tree)->left->type >= TK_COMMAND)
		pipe_for_command(&(*tree)->left, stdin_fd, process);
	if ((*tree)->right->type >= TK_FILE_IN && (*tree)->right->type <= TK_APPEND)
		solo_redirect((*tree)->right, stdin_fd);
	else if ((*tree)->right->type >= TK_COMMAND)
		pipe_for_command(&(*tree)->right, stdin_fd, process);
}

int	first_iteration(t_tree **tree, t_process **process)
{
	int	pipe_temp[2];
	int	stdin_fd;

	stdin_fd = -1;
	if ((*tree)->left->type >= TK_REDIR_IN && (*tree)->left->type <= TK_APPEND)
		solo_redirect((*tree)->left, &stdin_fd);
	else if ((*tree)->left->type == TK_COMMAND)
		pipe_for_command(&(*tree)->left, &stdin_fd, process);
	if ((*tree)->right->type >= TK_REDIR_IN && (*tree)->right->type <= TK_APPEND)
		solo_redirect((*tree)->right, &stdin_fd);
	else if ((*tree)->right->type == TK_COMMAND)
	{
		t_process	*temp;
		
		pipe(pipe_temp);
		process_add_back(process, node_process_creator((*tree)->right));
		temp = search_process(process, (*tree)->right);
		if (temp->pid == 0)
		{
			if (stdin_fd != -1)
			{
				dup2(stdin_fd, STDIN_FILENO);
				close(stdin_fd);
			}
			if ((*tree)->main != 1)
				dup2(pipe_temp[1], STDOUT_FILENO);
			close(pipe_temp[0]);
			close(pipe_temp[1]);
			exorcise((*tree)->right, -1);
		}
		else
		{
			if (stdin_fd != -1)
				close(stdin_fd);
			close(pipe_temp[1]);
			stdin_fd = pipe_temp[0];
		}
	}
	if ((*tree)->main != 1)
		(*tree) = (*tree)->prev;
	else
		close(stdin_fd);
	return (stdin_fd);
}

void	ft_pipe(t_tree **tree, int left_or_rigth)
{
	int	stdin_fd;
	t_tree	*current;
	t_process	*process;

	current = (*tree);
	process = NULL;
	stdin_fd = first_iteration(&current, &process);
	if (current->main == 1)
	{
		wait_free_process(&process);
		return ;
	}
	while (current->type == TK_PIPE && current->main == 1)
	{
		if (left_or_rigth == 1)
		{
			pipe_iteration(tree, &stdin_fd, &process);
			current = current->prev;
		}
		else
		{
			pipe_iteration(tree, &stdin_fd, &process);
			current = current->right;
		}
	}
}
