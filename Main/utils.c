/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 00:18:10 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/01 01:05:15 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	tokenizer_and_exec(t_arg_main *args)
{
	if (tokenizer(args) == 0)
	{
		free_tokens(args->tokens);
		free_split(args->matrix);
		exorcise_manager(&args->tree);
		args->tree = NULL;
	}
}

void	init_data(void)
{
	get_data()->exited_in_fork = false;
	get_data()->is_subshell = 0;
	get_data()->l_or_r = 0;
	get_data()->tokens = NULL;
	get_data()->exit_code = 0;
}

void	exec_consha(t_arg_main *args)
{
	signal(SIGINT, handle_sigint_no_redisplay);
	if (args->rdline[0] != '\0')
		tokenizer_and_exec(args);
	add_history(args->rdline);
}
