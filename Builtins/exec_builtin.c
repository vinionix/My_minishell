/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 01:43:49 by gada-sil          #+#    #+#             */
/*   Updated: 2025/05/15 22:18:08 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_builtin(char **matrix, t_env **envs, t_tree *tree)
{
	char	*command;

	command = matrix[0];
	if (!ft_strcmp(command, "exit"))
		return (ft_exit(matrix, tree, *envs));
	else if (!ft_strcmp(command, "env"))
		return (ft_env(*envs, matrix));
	else if (!ft_strcmp(command, "cd"))
		return (ft_cd(matrix, *envs));
	else if (!ft_strcmp(command, "export"))
		return (ft_export(matrix, envs));
	else if (!ft_strcmp(command, "echo") && matrix[1] && !ft_strcmp(matrix[1], "-n"))
		return (ft_echo_n(matrix));
	else if (!ft_strcmp(command, "echo"))
		return (ft_echo(matrix));
	else if (!ft_strcmp(command, "unset"))
		return (ft_unset(matrix, envs));
	else if (!ft_strcmp(command, "pwd"))
		return (ft_pwd(matrix));
	return (1337);
}
