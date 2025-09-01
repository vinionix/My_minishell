/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 03:51:03 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/31 22:51:59 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	g_signal_v = 0;

void	set_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, handle_sigint);
}

void	handle_sigint_no_redisplay(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_signal_v++;
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_signal_v++;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	handle_sigint_in_fork(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			get_data()->exited_in_fork = true;
			if (get_data()->is_subshell)
				get_data()->exit_code = 130;
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
		change_var(get_data()->env, "?=", ft_strdup("130"));
	}
	else if (g_signal_v == 1 && get_data()->exited_in_fork)
	{
		change_var(get_data()->env, "?=", ft_itoa(save_code));
		get_data()->exited_in_fork = false;
	}
	else if (g_signal_v == 1 && !get_data()->exited_in_fork)
	{
		get_data()->exit_code = 130;
		change_var(get_data()->env, "?=", ft_strdup("130"));
	}
	g_signal_v = 0;
}
