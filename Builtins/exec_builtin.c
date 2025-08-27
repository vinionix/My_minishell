/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 01:43:49 by gada-sil          #+#    #+#             */
/*   Updated: 2025/08/27 15:30:18 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_builtin(char *command)
{
	return (!ft_strcmp(command, "exit") || !ft_strcmp(command, "env")
		|| !ft_strcmp(command, "cd") || !ft_strcmp(command, "export")
		|| !ft_strcmp(command, "echo") || !ft_strcmp(command, "unset")
		|| !ft_strcmp(command, "pwd"));
}

int	exec_builtin(char ***matrix, t_env **envs, t_tree *tree)
{
	if (is_builtin((*matrix)[0]))
		(*matrix) = expand_and_quotes((*matrix), get_data()->env);
	if (!ft_strcmp((*matrix)[0], "exit"))
		return (ft_exit((*matrix), tree, *envs));
	else if (!ft_strcmp((*matrix)[0], "env"))
		return (ft_env(*envs, (*matrix)));
	else if (!ft_strcmp((*matrix)[0], "cd"))
		return (ft_cd((*matrix), *envs));
	else if (!ft_strcmp((*matrix)[0], "export") && !(*matrix)[1])
		return (export_no_args(*envs));
	else if (!ft_strcmp((*matrix)[0], "export"))
		return (ft_export((*matrix), envs));
	else if (!ft_strcmp((*matrix)[0], "echo") && (*matrix)[1]
		&& !ft_strcmp((*matrix)[1], "-n"))
		return (ft_echo_n((*matrix)));
	else if (!ft_strcmp((*matrix)[0], "echo"))
		return (ft_echo((*matrix)));
	else if (!ft_strcmp((*matrix)[0], "unset"))
		return (ft_unset((*matrix), envs));
	else if (!ft_strcmp((*matrix)[0], "pwd"))
		return (ft_pwd((*matrix)));
	return (1337);
}
