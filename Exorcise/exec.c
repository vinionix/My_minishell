/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 01:43:49 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/01 01:26:23 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_command_error(t_tree *current_node)
{
	char	*command;

	command = current_node->u_define.command.cmd[0];
	if (is_command_directory(command))
	{
		write(2, "miniconsha: ", 13);
		write(2, command, ft_strlen(command));
		ft_putendl_fd(" Is a directory", 2);
		return (126);
	}
	else
	{
		ft_putstr_fd(command, 2);
		ft_putendl_fd(": command not found", 2);
	}
	return (127);
}

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
