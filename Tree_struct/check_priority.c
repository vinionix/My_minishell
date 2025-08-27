/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_priority.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/27 15:23:28 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_priority(t_token **tokens, int i, int *receiver, int *flag)
{
	if ((*tokens)[i].type == TK_PIPE && *flag != 1 && *flag != 2
			&& *flag != 3)
	{
		*flag = 3;
		*receiver = i;
	}
	else if ((*tokens)[i].type == TK_COMMAND && *flag != 1 && *flag != 2
			&& *flag != 3 && *flag != 4)
	{
		*flag = 4;
		*receiver = i;
	}
	else if ((*tokens)[i].type >= TK_REDIR_IN && (*tokens)[i].type <= TK_HEREDOC
			&& *flag != 1 && *flag != 2 && *flag != 3 && *flag != 4
			&& *flag != 5)
	{
		*flag = 5;
		*receiver = i;
	}
}
