/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:57:58 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/29 13:00:05 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static void	exec_bin(t_tree *current_node)
{
	char	**path;
	char	**env_exe;

	path = get_path(get_data()->env);
	env_exe = env_execv(get_data()->env);
	current_node->u_define.command.cmd
		= expand_and_wildcard(current_node->u_define.command.cmd,
			get_data()->env);
	valid_path(current_node->u_define.command.cmd, path);
	execve(current_node->u_define.command.cmd[0],
		current_node->u_define.command.cmd, env_exe);
	dup2(1, STDOUT_FILENO);
	printf("%s: command not found\n", current_node->u_define.command.cmd[0]);
	free_matrix(path);
	free_matrix(env_exe);
	free_tree_and_env();
	exit(127);
}

void	exorcise(t_tree *current_node, t_process *process)
{
	int	exit_code;

	exit_code = 0;
	if (process)
		free_process(&process);
	if (if_redirect(current_node->u_define.command.list_redir) == -1)
	{
		free_tree_and_env();
		exit (1);
	}
	exit_code = exec_builtin(&current_node->u_define.command.cmd,
			&get_data()->env, current_node);
	get_data()->exit_code = exit_code;
	if (get_data()->exit_code == 1337)
		exec_bin(current_node);
	free_tree_and_env();
	exit(get_data()->exit_code);
}

static void	exec_main_node(t_tree *current_node, int is_subshell)
{
	if (current_node->type == TK_AND && (get_data()->exit_code == 0
			|| get_data()->exit_code == -1))
		tk_and(current_node);
	else if (current_node->type == TK_OR && get_data()->exit_code != 0)
		tk_or(current_node);
	else if (current_node->type == TK_PIPE)
		ft_pipe(&current_node, 1);
	else if (current_node->type >= TK_REDIR_IN
		&& current_node->type <= TK_HEREDOC)
		creat_solo_redirect(current_node->u_define.command.list_redir);
	else if (current_node->type == TK_COMMAND)
		exec_command_solo(current_node);
	else if (current_node->type == TK_SUBSHELL)
		exec_subshell(current_node->subtree);
	free_tree(get_data()->head);
	if (is_subshell)
	{
		free_list(get_data()->env);
		exit(get_data()->exit_code);
	}
}

static void	exec_tree(t_tree *current_node, int is_subshell)
{
	while (current_node)
	{
		if (current_node->type == TK_PIPE)
			ft_pipe(&current_node, 1);
		if (current_node->type == TK_AND && (get_data()->exit_code == 0
				|| get_data()->exit_code == -1))
			tk_and(current_node);
		if (current_node->type == TK_OR && get_data()->exit_code != 0)
			tk_or(current_node);
		if (current_node->type == TK_SUBSHELL)
			exec_subshell(current_node);
		current_node = current_node->prev;
	}
	free_tree(get_data()->head);
	if (is_subshell)
	{
		free_list(get_data()->env);
		exit(get_data()->exit_code);
	}
}

void	exorcise_manager(t_tree **tree, int is_subshell)
{
	t_tree	*current_node;

	get_data()->exit_code = -1;
	current_node = last_left(*tree);
	if (current_node->main == 1)
	{
		exec_main_node(current_node, is_subshell);
		return ;
	}
	exec_tree(current_node, is_subshell);
}
