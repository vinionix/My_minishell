/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 03:51:03 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/29 14:09:57 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_first_token(t_token **tokens, int i)
{
	if ((*tokens)[i].id == 0 && (*tokens)[i].type == TK_PIPE)
	{
		print_error("minishell: syntax error near unexpected token",
			(*tokens)[i].value);
		return (1);
	}
	return (0);
}

int	check_last_token(t_token **tokens, int i)
{
	if ((*tokens)[i + 1].value == NULL && (*tokens)[i].type <= TK_HEREDOC)
	{
		print_error("minishell: syntax error near unexpected token `newline'",
			NULL);
		return (1);
	}
	return (0);
}

int	check_consecutive_operators(t_token **tokens, int i)
{
	if (i > 0 && ((*tokens)[i].type == TK_PIPE)
		&& ((*tokens)[i - 1].type >= TK_REDIR_IN
		&& (*tokens)[i - 1].type <= TK_PIPE))
	{
		print_error("minishell: syntax error near unexpected token",
			(*tokens)[i].value);
		return (1);
	}
	return (0);
}
