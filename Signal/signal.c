/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 03:51:03 by vfidelis          #+#    #+#             */
/*   Updated: 2025/05/26 13:13:32 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t signal_v = 0;

void set_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	signal_v = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int handle_sigint_in_fork(int status, pid_t pid)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			get_data()->exited_in_fork = true;
			get_data()->should_redisplay = false;
			kill(SIGINT, pid);
			return (1);
		}
	}
	return (0);
}
