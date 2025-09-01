/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_redirect_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 01:43:49 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/01 01:24:45 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

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
			perror("miniconsha: fail to open file");
		}
		else
		{
			get_data()->exit_code = 0;
			if (current_fd >= 0)
				close(current_fd);
		}
		redir = redir->next;
	}
}
