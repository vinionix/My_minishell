/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_priority.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/07/11 14:50:35 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_priority(t_token **tokens, int i, int *receiver, int *flag)
{
	if ((((*tokens)[i].type == TK_AND || (*tokens)[i].type == TK_OR)
		&& *flag != 1))
	{
		*flag = 1;
		*receiver = i;
	}
	else if	((*tokens)[i].type == TK_SUBSHELL && *flag != 1 && *flag != 2)
	{
		*flag = 2;
		*receiver = i;
	}
	else if ((*tokens)[i].type == TK_PIPE && *flag != 1 && *flag != 2 && *flag != 3)
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
		&& *flag != 1 && *flag != 2 && *flag != 3 && *flag != 4 && *flag != 5)
	{
		*flag = 5;
		*receiver = i;
	}
}
