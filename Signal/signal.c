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

void set_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
}

void	handle_sigint(int sig)
{
	(void)sig;
	change_env_var(get_data()->env, "?=", ft_itoa(130));
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*int handle_sigint_in_fork(int status, int pid)
{
	if (WIFEXITED(status))
		get_data()->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		get_data()->exit_code = 128 + WTERMSIG(status);
		printf("\n%d\n", get_data()->exit_code);
		if (WTERMSIG(status) == SIGINT)
		{
			kill(SIGINT, pid);
			return (1);
		}
	}
	return (0);
}*/
