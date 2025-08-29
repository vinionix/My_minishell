/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 03:51:03 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/29 14:07:07 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	check_first_token(t_token **tokens, int i)
{
	if ((*tokens)[i].id == 0 && (*tokens)[i].type >= TK_PIPE
		&& (*tokens)[i].type <= TK_FINAL_PAREN)
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
	int	flag_error;

	flag_error = 0;
	if (i > 0 && ((*tokens)[i].type >= TK_PIPE
		&& (*tokens)[i].type <= TK_FINAL_PAREN) && ((*tokens)[i
			- 1].type >= TK_REDIR_IN && (*tokens)[i - 1].type <= TK_OR))
		flag_error = 1;
	else if (((*tokens)[i].type == TK_INIT_PAREN
		&& (*tokens)[i + 1].type >= TK_PIPE
		&& (*tokens)[i + 1].type <= TK_FINAL_PAREN)
		|| ((*tokens)[i].type == TK_FINAL_PAREN
		&& (*tokens)[i + 1].type == TK_INIT_PAREN))
		flag_error = 1;
	else if ((((*tokens)[i].type >= TK_REDIR_IN && (*tokens)[i].type <= TK_PIPE)
		|| (*tokens)[i].type == TK_COMMAND)
			&& (*tokens)[i + 1].type == TK_INIT_PAREN)
		flag_error = 1;
	if (flag_error == 1)
	{
		print_error("minishell: syntax error near unexpected token",
			(*tokens)[i].value);
	}
	return (flag_error);
}

int	check_init_paren(t_token **tokens, int i, int *count_init_paren)
{
	if ((*tokens)[i].type == TK_INIT_PAREN)
	{
		(*count_init_paren)++;
		if (i > 0)
		{
			if (((*tokens)[i + 1].value == NULL
				&& (*tokens)[i - 1].type >= TK_FILE_IN)
				|| ((*tokens)[i - 1].type >= TK_REDIR_IN
				&& (*tokens)[i - 1].type <= TK_HEREDOC)
				|| ((*tokens)[i + 1].type == TK_FINAL_PAREN))
			{
				print_error("minishell: syntax error near unexpected token",
					(*tokens)[i + 1].value);
				return (1);
			}
		}
	}
	return (0);
}

int	check_final_paren(t_token **tokens, int i, int *count_final_paren,
		int count_init_paren)
{
	if ((*tokens)[i].type == TK_FINAL_PAREN)
	{
		(*count_final_paren)++;
		if (*count_final_paren > count_init_paren)
		{
			print_error("minishell: syntax error near unexpected token `)'",
				NULL);
			return (1);
		}
	}
	return (0);
}
