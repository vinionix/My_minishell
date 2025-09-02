/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:12:48 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/29 20:16:12 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../consha.h"

t_process	*search_process(t_process **process, t_tree *current_node)
{
	t_process	*temp;

	temp = (*process);
	while (temp->id_tree != current_node->id_tree)
		temp = temp->next;
	temp->pid = fork();
	return (temp);
}

void	free_process(t_process **process)
{
	t_process	*temp;

	temp = *process;
	while (temp)
	{
		temp = (*process)->next;
		free(*process);
		(*process) = temp;
	}
}

void	wait_free_process(t_process **process)
{
	t_process	*temp;
	int			status;

	temp = (*process);
	while (temp != NULL)
	{
		waitpid(temp->pid, &status, 0);
		handle_sigint_in_fork(status);
		get_data()->exit_code = WEXITSTATUS(status);
		temp = temp->next;
	}
	free_process(process);
	change_var(get_data()->env, "?=", ft_itoa(get_data()->exit_code));
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

void	verify_stdin(int *stdin_fd)
{
	if (*stdin_fd != -1)
	{
		dup2(*stdin_fd, STDIN_FILENO);
		close(*stdin_fd);
	}
}
