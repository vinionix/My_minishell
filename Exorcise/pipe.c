/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 22:40:32 by vfidelis          #+#    #+#             */
/*   Updated: 2025/07/23 08:11:41 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_process	*search_process(t_process **process, t_tree *current_node)
{
	t_process	*temp;

	temp = (*process);
	while (temp->id_tree != current_node->id_tree)
		temp = temp->next;
	temp->pid = fork();
	return (temp);
}

void	wait_free_processs(t_process **process)
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
	wait(NULL);
	while ((*process))
	{
		temp = (*process);
		(*process) = (*process)->next;
		free(temp);
	}
}