/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 22:40:32 by vfidelis          #+#    #+#             */
/*   Updated: 2025/07/21 05:32:13 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    first_iteration(t_process **process, t_tree *current_node)
{
	t_process	*temp;

	pipe(current_node->u_define.pipe.pipefd);
    process_add_back(process, node_process_creator(current_node->left));
    temp = (*process);
    while (temp->id_tree != current_node->left->id_tree)
		temp = temp->next;
    temp->pid = fork();
    if (temp->pid == 0)
    	exorcise(current_node->left, 0);
    else
    {
		close(current_node->u_define.pipe.pipefd[1]);
		dup2(current_node->u_define.pipe.pipefd[0], STDIN_FILENO);
		close(current_node->u_define.pipe.pipefd[0]);
    }
}

t_process	*search_process(t_process **process, t_tree *current_node)
{
	t_process	*temp;

	temp = (*process);
	while (temp->id_tree != current_node->id_tree)
		temp = temp->next;
	temp->pid = fork();
	return (temp);
}

void	wait_free_processs(t_process **process, int saved_stdin)
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
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
}

void	last_iteration(t_process **process, t_tree *current_node)
{
	t_process	*temp;
	
	process_add_back(process, node_process_creator(current_node->right));
	temp = search_process(process, current_node->right);
	if (temp->pid == 0)
		exorcise(current_node->right, 2);
}
void	tk_pipe_left(t_tree **current_node, t_process **process)
{
	t_process	*temp;

	if ((*current_node)->left && (*current_node)->left->type == TK_COMMAND)
		first_iteration(process, (*current_node));
	else if ((*current_node)->left && (*current_node)->left->type >= TK_REDIR_IN
			&& (*current_node)->left->type <= TK_HEREDOC)
		creat_solo_redirect((*current_node)->left->u_define.command.list_redir);
	if ((*current_node)->right && (*current_node)->right->type == TK_COMMAND)
	{
		process_add_back(process, node_process_creator((*current_node)->right));
		temp = search_process(process, (*current_node)->right);
		if (temp->pid == 0)
		exorcise((*current_node)->right, 1);
		else if ((*current_node)->prev && (*current_node)->prev->type == TK_PIPE)
		{
			pipe((*current_node)->prev->u_define.pipe.pipefd);
			close((*current_node)->prev->u_define.pipe.pipefd[1]);
			dup2((*current_node)->prev->u_define.pipe.pipefd[0], STDIN_FILENO);
			close((*current_node)->prev->u_define.pipe.pipefd[0]);
		}
	}
	else if ((*current_node)->right && (*current_node)->right->type >= TK_REDIR_IN
			&& (*current_node)->right->type <= TK_HEREDOC)
		creat_solo_redirect((*current_node)->right->u_define.command.list_redir);
}

void	tk_pipe_right(t_tree *current_node)
{
	int			saved_stdin;
	t_process	*process;
	t_process	*temp;
	
	process = NULL;
	saved_stdin = dup(STDIN_FILENO);
	if (current_node->left->type == TK_COMMAND)
		first_iteration(&process, current_node);
	while (current_node && current_node->type == TK_PIPE)
	{
		if (current_node->right->type == TK_COMMAND)
		{
			last_iteration(&process, current_node);
			break ;
		}
		else if (current_node->right->type >= TK_REDIR_IN && current_node->right->type <= TK_HEREDOC)
			creat_solo_redirect(current_node->right->u_define.command.list_redir);
		if (current_node->left->type == TK_COMMAND)
		{
			process_add_back(&process, node_process_creator(current_node->left));
			temp = search_process(&process, current_node->left);
			if (temp->pid == 0)
				exorcise(current_node->left, 2);
			else if (current_node->right && current_node->right->type == TK_PIPE)
			{
				pipe(current_node->right->u_define.pipe.pipefd);
				close(current_node->right->u_define.pipe.pipefd[1]);
				dup2(current_node->right->u_define.pipe.pipefd[0], STDIN_FILENO);
				close(current_node->right->u_define.pipe.pipefd[0]);
			}
		}
		else if (current_node->left->type >= TK_REDIR_IN && current_node->left->type <= TK_HEREDOC)
			creat_solo_redirect(current_node->left->u_define.command.list_redir);
		current_node = current_node->right;
	}
	wait_free_processs(&process, saved_stdin);
}
