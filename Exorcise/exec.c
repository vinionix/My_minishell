/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 01:43:49 by gada-sil          #+#    #+#             */
/*   Updated: 2025/08/29 19:36:23 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_command_solo(t_tree *current_node)
{
	int		status;
	pid_t	pid;

	status = 0;
	if ((current_node->u_define.command.list_redir
			&& !is_builtin(current_node->u_define.command.cmd[0]))
		|| !is_builtin(current_node->u_define.command.cmd[0]))
	{
		pid = fork();
		if (pid == 0)
			exorcise(current_node, NULL);
		else
		{
			waitpid(pid, &status, 0);
			get_data()->exit_code = WEXITSTATUS(status);
			change_var(get_data()->env, "?=", ft_itoa(get_data()->exit_code));
		}
	}
	else
	{
		status = exec_builtin(&current_node->u_define.command.cmd,
				&get_data()->env, current_node);
		get_data()->exit_code = status;
		change_var(get_data()->env, "?=", ft_itoa(get_data()->exit_code));
	}
}
