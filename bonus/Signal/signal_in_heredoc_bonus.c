/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_in_heredoc_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 03:51:03 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/27 15:48:55 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	handle_sigint_in_heredoc(int status, pid_t pid)
{
	if (WEXITSTATUS(status) == 130)
	{
		get_data()->exited_in_fork = true;
		kill(SIGINT, pid);
		return (1);
	}
	return (0);
}
