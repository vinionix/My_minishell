/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:57:58 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/12 19:13:36 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree *last_left(t_tree *tree)
{
	if (!tree)
		return (NULL);
	while (tree->left && tree->left->type != TK_COMMAND
		&& tree->left->type != TK_SUBSHELL
		&& !(tree->left->type >= TK_REDIR_IN && tree->left->type <= TK_HEREDOC))
		tree = tree->left;
	return (tree);
}

t_process *node_process_creator(t_tree *node)
{
	t_process *node_process;

	node_process = malloc(sizeof(t_process));
	node_process->prev = NULL;
	node_process->next = NULL;
	node_process->pid = -1;
	node_process->id_tree = node->id_tree;
	return (node_process);
}

void process_add_back(t_process **main, t_process *node)
{
	t_process *temp;

	temp = (*main);
	if ((*main) == NULL)
	{
		*main = node;
		return;
	}
	while ((*main)->next != NULL)
		*main = (*main)->next;
	node->prev = *main;
	(*main)->next = node;
	*main = temp;
}

static char	**env_execv(t_env *env)
{
	char	*full_join;
	char	**env_exe;
	t_env	*temp;
	int		i;

	i = 0;
	temp = env;
	while(temp)
	{
		i++;
		temp = temp->next;
	}
	env_exe = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while(env)
	{
		full_join = ft_strjoin(env->key, "=");
		env_exe[i] = ft_strjoin(full_join, env->value);
		i++;
		free(full_join);
		env = env->next;
	}
	return (env_exe);
}

void	exorcise(t_tree *current_node, int flag, int std_out)
{
	char	**path;
	char	**env_exe;
	int		current_fd;
	t_redir	*temp;

	path = NULL;
	(void)flag;
	env_exe = NULL;
	current_fd = 0;
	temp = current_node->u_define.command.list_redir;
	if (temp)
	{
		while(temp)
		{
			if (temp->type == TK_EOF)
			{
				if (temp->fd_heredoc == -1)
				{
					close(temp->fd_heredoc);
					exit(130);
				}
				dup2(temp->fd_heredoc, STDIN_FILENO);
				close(temp->fd_heredoc);
			}
			else if (temp->type == TK_FILE_APP)
			{
				current_fd = open(temp->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
				if (current_fd == -1)
					perror("minishell$");
				else
				{
					dup2(current_fd, STDOUT_FILENO);
					close(current_fd);
				}
			}
			else if (temp->type == TK_FILE_OUT)
			{
				current_fd = open(temp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

				if (current_fd == -1)
					perror("minishell$");
				else
				{
					dup2(current_fd, STDOUT_FILENO);
					close(current_fd);
				}
			}
			else if (temp->type == TK_FILE_IN)
			{
				current_fd = open(temp->file, O_RDONLY);
				if (current_fd == -1)
					perror("minishell$");
				else
				{
					dup2(current_fd, STDIN_FILENO);
					close(current_fd);
				}
			}
			temp = temp->next;
		}
	}
	get_data()->exit_code = exec_builtin(&current_node->u_define.command.cmd,
		&get_data()->env, get_data()->head);
	if (get_data()->exit_code == 1337)
	{
		path = get_path(get_data()->env);
		env_exe = env_execv(get_data()->env);
		current_node->u_define.command.cmd = expand_and_wildcard(current_node->u_define.command.cmd, get_data()->env);
		valid_path(current_node->u_define.command.cmd, path);
		execve(current_node->u_define.command.cmd[0], current_node->u_define.command.cmd, env_exe);
		dup2(std_out, STDOUT_FILENO);
		printf("%s: command not found\n", current_node->u_define.command.cmd[0]);
		exit(127);
	}
	/* teoricamente não muda nada esses frees */
	free_tree(get_data()->head);
	free_list(get_data()->env);
	get_data()->head = NULL;
	get_data()->env = NULL;
	exit(get_data()->exit_code);
}

t_data *get_data(void)
{
	static t_data data;

	return (&data);
}

void	creat_solo_redirect(t_redir *redir)
{
	int	current_fd;

	current_fd = -2;
	while (redir)
	{
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
			if (current_fd != 0)
				close(current_fd);
		}
		redir = redir->next;
	}
}

void	exec_command_solo(t_tree **current_node)
{
	int		status;
	pid_t	pid;

	status = 0;
	if ((*current_node)->u_define.command.list_redir
		|| !is_builtin((*current_node)->u_define.command.cmd[0]))
	{
		pid = fork();
		if (pid == 0)
			exorcise((*current_node), -1, 1);
		else
		{
			waitpid(pid, &status, 0);
			get_data()->exit_code = WEXITSTATUS(status);
			change_env_var(get_data()->env, "?=", ft_itoa(get_data()->exit_code));
		}
	}
	else
	{
		get_data()->exit_code = exec_builtin(&(*current_node)->u_define.command.cmd,
			&get_data()->env, get_data()->head);
		change_env_var(get_data()->env, "?=", ft_itoa(get_data()->exit_code));
	}
}

void	exec_subshell(t_tree *subtree)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		get_data()->is_subshell = 1;
		exorcise_manager(&subtree, 1);
	}
	else
	{
		waitpid(pid, &status, 0);
		get_data()->exit_code = WEXITSTATUS(status);
		change_env_var(get_data()->env, "?=", ft_itoa(get_data()->exit_code));
	}
}

void	tk_or(t_tree **current_node)
{
	if ((*current_node)->left->type == TK_SUBSHELL)
		exec_subshell((*current_node)->left->subtree);
	else if ((*current_node)->left->type == TK_COMMAND)
		exec_command_solo(&(*current_node)->left);
	else if ((*current_node)->left->type >= TK_REDIR_IN
		&& (*current_node)->left->type <= TK_HEREDOC)
		creat_solo_redirect((*current_node)->left->u_define.command.list_redir);
	if ((*current_node)->right->type == TK_SUBSHELL && get_data()->exit_code != 0)
		exec_subshell((*current_node)->right->subtree);
	else if ((*current_node)->right->type == TK_PIPE && get_data()->exit_code != 0)
		ft_pipe(&(*current_node)->right, 0);
	else if ((*current_node)->right->type == TK_COMMAND
		&& get_data()->exit_code != 0)
		exec_command_solo(&(*current_node)->right);
	else if ((*current_node)->right->type >= TK_REDIR_IN
		&& (*current_node)->right->type <= TK_HEREDOC && get_data()->exit_code != 0)
		creat_solo_redirect((*current_node)->right->u_define.command.list_redir);
}

void	tk_and(t_tree **current_node)
{
	if ((*current_node)->left->type == TK_SUBSHELL)
		exec_subshell((*current_node)->left->subtree);
	else if ((*current_node)->left->type == TK_COMMAND)
		exec_command_solo(&(*current_node)->left);
	else if ((*current_node)->left->type >= TK_REDIR_IN
		&& (*current_node)->left->type <= TK_HEREDOC)
		creat_solo_redirect((*current_node)->left->u_define.command.list_redir);
	if ((*current_node)->right->type == TK_SUBSHELL && get_data()->exit_code == 0)
		exec_subshell((*current_node)->right->subtree);
	else if ((*current_node)->right->type == TK_PIPE && get_data()->exit_code == 0)
		ft_pipe(&(*current_node)->right, 0);
	else if ((*current_node)->right->type == TK_COMMAND
		&& get_data()->exit_code == 0)
		exec_command_solo(&(*current_node)->right);
	else if ((*current_node)->right->type >= TK_REDIR_IN
		&& (*current_node)->right->type <= TK_HEREDOC && get_data()->exit_code == 0)
		creat_solo_redirect((*current_node)->right->u_define.command.list_redir);
}

void exorcise_manager(t_tree **tree, int is_subshell)
{
	t_tree	*current_node;

	get_data()->exit_code = -1;
	current_node = last_left(*tree);
	if (!current_node)
		return ;
	if (current_node->main == 1)
	{
		if (current_node->type == TK_AND && (get_data()->exit_code == 0
			|| get_data()->exit_code == -1))
			tk_and(&current_node);
		else if (current_node->type == TK_OR && get_data()->exit_code != 0)
			tk_or(&current_node);
		else if (current_node->type == TK_PIPE)
			ft_pipe(&current_node, 1);
		else if (current_node->type >= TK_REDIR_IN && current_node->type <= TK_HEREDOC)
			creat_solo_redirect(current_node->u_define.command.list_redir);
		else if (current_node->type == TK_COMMAND)
			exec_command_solo(&current_node);
		else if (current_node->type == TK_SUBSHELL)
			exec_subshell(current_node->subtree);
		free_tree(*tree);
		if (is_subshell)
			exit(get_data()->exit_code);
		return ;
	}
	while (current_node)
	{
		if (current_node->type == TK_PIPE)
			ft_pipe(&current_node, 1);
		else if (current_node->type == TK_AND && (get_data()->exit_code == 0
			|| get_data()->exit_code == -1))
			tk_and(&current_node);
		else if (current_node->type == TK_OR && get_data()->exit_code != 0)
			tk_or(&current_node);
		else if (current_node->type == TK_SUBSHELL)
			exec_subshell(current_node);
		current_node = current_node->prev;
	}
	free_tree(*tree);
	if (is_subshell)
		exit(get_data()->exit_code);
}
