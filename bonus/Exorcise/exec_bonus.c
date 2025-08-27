/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 01:43:49 by gada-sil          #+#    #+#             */
/*   Updated: 2025/08/27 15:45:35 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	exec_command_solo(t_tree *current_node)
{
	int		status;
	pid_t	pid;

	status = 0;
	if (current_node->u_define.command.list_redir
		|| !is_builtin(current_node->u_define.command.cmd[0]))
	{
		pid = fork();
		if (pid == 0)
			exorcise(current_node, 1);
		else
		{
			waitpid(pid, &status, 0);
			get_data()->exit_code = WEXITSTATUS(status);
			change_env_var(get_data()->env, "?=",
				ft_itoa(get_data()->exit_code));
		}
	}
	else
	{
		status = exec_builtin(&current_node->u_define.command.cmd,
				&get_data()->env, get_data()->head);
		get_data()->exit_code = status;
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
