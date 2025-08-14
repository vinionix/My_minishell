/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 03:51:03 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/12 20:45:55 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	g_signal_v = 0;

void	set_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, handle_sigint);
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_signal_v++;
	if (rl_readline_state & RL_STATE_READCMD)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sigkill(int sig)
{
	(void)sig;
	exit(130);
}

int	handle_sigint_in_fork(int status, pid_t pid)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			get_data()->exited_in_fork = true;
			kill(SIGINT, pid);
			return (1);
		}
	}
	return (0);
}

void	handle_sigint_code(void)
{
	int	save_code;

	save_code = get_data()->exit_code;
	if (g_signal_v >= 2)
	{
		get_data()->exit_code = 130;
		change_env_var(get_data()->env, "?=", ft_strdup("130"));
	}
	else if (g_signal_v == 1 && get_data()->exited_in_fork)
	{
		change_env_var(get_data()->env, "?=", ft_itoa(save_code));
		get_data()->exited_in_fork = false;
	}
	else if (g_signal_v == 1 && !get_data()->exited_in_fork)
	{
		get_data()->exit_code = 130;
		change_env_var(get_data()->env, "?=", ft_strdup("130"));
	}
	g_signal_v = 0;
}
