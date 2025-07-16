/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:57:58 by vfidelis          #+#    #+#             */
/*   Updated: 2025/07/16 16:21:22 by vfidelis         ###   ########.fr       */
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

static char	**env_execv(t_env *env)
{
	
	t_env	*temp;	
	int		i;
	char	**env_exe;

	i = 0;
	temp = env;
	while(temp)
	{
		i++;
		temp = temp->next;
	}
	env_exe = malloc(sizeof(char *) * (i + 1));
	env_exe[i] = NULL;
	i = 0;
	while(env)
	{
		env_exe[i] = env->full;
		i++;
		env = env->next;
	}
	return (env_exe);
}
void	exorcise(t_tree *current_node, int flag)
{
	char	**path;
	char	**env_exe;
	int		current_fd;

	path = NULL;
	env_exe = NULL;
	current_fd = 0;
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
			close(current_node->prev->prev->u_define.pipe.pipefd[1]);
			close(current_node->prev->prev->u_define.pipe.pipefd[0]);
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
	if (current_node->u_define.command.list_redir)
	{
		while(current_node->u_define.command.list_redir)
		{
			// if (current_node->u_define.command.list_redir->type == TK_HEREDOC)
			//	here(current_node->u_define.command.list_redir->eof);
			if (current_node->u_define.command.list_redir->type == TK_FILE_APP)
			{
				current_fd = open(current_node->u_define.command.list_redir->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
				if (current_fd == -1)
					perror("minishell$");
				else
				{
					dup2(current_fd, STDOUT_FILENO);
					close(current_fd);
				}
			}
			else if (current_node->u_define.command.list_redir->type == TK_FILE_OUT)
			{
				current_fd = open(current_node->u_define.command.list_redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

				if (current_fd == -1)
					perror("minishell$");
				else
				{
					dup2(current_fd, STDOUT_FILENO);
					close(current_fd);
				}
			}
			else if (current_node->u_define.command.list_redir->type == TK_FILE_IN)
			{
				current_fd = open(current_node->u_define.command.list_redir->file, O_RDONLY);
				if (current_fd == -1)
					perror("minishell$");
				else
				{
					dup2(current_fd, STDIN_FILENO);
					close(current_fd);
				}
			}
			current_node->u_define.command.list_redir = current_node->u_define.command.list_redir->next;
		}
	}
	path = get_path(get_data()->env);
	env_exe = env_execv(get_data()->env);
	valid_path(current_node->u_define.command.cmd, path);
	execve(current_node->u_define.command.cmd[0], current_node->u_define.command.cmd, env_exe);
	exit(1);
}

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

void	creat_solo_redirect(t_redir *redir)
{
	int	current_fd;

	current_fd = 0;
	while (redir)
	{
		/*if ((*current_node)->left->u_define.command.list_redir->type == TK_HEREDOC)
			here();*/
		if (redir->type == TK_FILE_APP)
			current_fd = open(redir->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else if (redir->type == TK_FILE_OUT)
			current_fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == TK_FILE_IN)
			current_fd = open(redir->file, O_RDONLY);
		if (current_fd == -1)
		{
			get_data()->exit_code = 1;
			perror("minishell$");
		}
		else
		{
			get_data()->exit_code = 0;
			close(current_fd);
		}
		redir = redir->next;
	}
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
	else if ((*current_node)->left->type >= TK_REDIR_IN && (*current_node)->left->type <= TK_HEREDOC)
		creat_solo_redirect((*current_node)->left->u_define.command.list_redir);
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
	else if ((*current_node)->right->type >= TK_REDIR_IN && (*current_node)->right->type <= TK_HEREDOC && get_data()->exit_code != 0)
		creat_solo_redirect((*current_node)->right->u_define.command.list_redir);
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
	else if ((*current_node)->left->type >= TK_REDIR_IN && (*current_node)->left->type <= TK_HEREDOC)
		creat_solo_redirect((*current_node)->left->u_define.command.list_redir);
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
	else if ((*current_node)->right->type >= TK_REDIR_IN && (*current_node)->right->type <= TK_HEREDOC && get_data()->exit_code == 0)
		creat_solo_redirect((*current_node)->right->u_define.command.list_redir);
}
void	exorcise_manager(t_tree **tree)
{
	t_tree		*current_node;
	t_process	*process;
	int			saved_stdin;

	get_data()->exit_code = -1;
	process = NULL;
	current_node = last_left((*tree));
	saved_stdin = dup(STDIN_FILENO);
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
		if (current_node && current_node->type == TK_AND && (get_data()->exit_code == 0
				|| get_data()->exit_code == -1))
		{
			if (process)
				wait_free_processs(&process, saved_stdin);
			tk_and(&current_node);
		}
		else if (current_node && current_node->type == TK_OR && get_data()->exit_code != 0)
		{
			if (process)
				wait_free_processs(&process, saved_stdin);
			tk_or(&current_node);
		}
		if (current_node && current_node->type == TK_PIPE)
			tk_pipe_left(&current_node, &process);
		current_node = current_node->prev;
	}
	if (process)
		wait_free_processs(&process, saved_stdin);
	//printf("\nsaida = %d\n", get_data()->exit_code);
}
