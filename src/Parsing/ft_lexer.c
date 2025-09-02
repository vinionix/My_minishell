/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:49:33 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/27 15:05:11 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../consha.h"

static void	ft_word_command_env(t_token **tokens)
{
	int	i;

	i = -1;
	while ((*tokens)[++i].value != NULL)
	{
		if ((*tokens)[i].type == 0)
		{
			if ((*tokens)[i].id == 0 || ((*tokens)[i - 1].type >= TK_PIPE
					&& (*tokens)[i - 1].type <= TK_OR) || ((*tokens)[i
					- 1].type >= TK_FILE_IN && (*tokens)[i - 1].type <= TK_EOF)
				|| (*tokens)[i - 1].type == TK_INIT_PAREN)
				(*tokens)[i].type = TK_COMMAND;
		}
		if ((*tokens)[i].type == TK_COMMAND)
		{
			while ((*tokens)[++i].value && (!((*tokens)[i].type >= TK_PIPE
						&& (*tokens)[i].type <= TK_OR)))
			{
				if ((*tokens)[i].type == 0)
					(*tokens)[i].type = TK_CMD_ARG;
			}
			i--;
		}
	}
}

static void	ft_eof(t_token **tokens)
{
	int	i;

	i = 0;
	while ((*tokens)[i].value != NULL)
	{
		if ((*tokens)[i].type == TK_HEREDOC && (*tokens)[i].type == 0)
		{
			if ((*tokens)[i + 1].value)
				(*tokens)[i].type = TK_EOF;
		}
		i++;
	}
}

static void	ft_file_redir(t_token **tokens)
{
	int	i;

	i = 0;
	while ((*tokens)[i].value != NULL)
	{
		if ((*tokens)[i + 1].value && (*tokens)[i].type == TK_REDIR_IN &&
			(chr_separator((*tokens)[i + 1].value, 0) == 0 ||
				ft_strlen((*tokens)[i + 1].value) > 2))
			(*tokens)[i + 1].type = TK_FILE_IN;
		else if ((*tokens)[i + 1].value && (*tokens)[i].type == TK_REDIR_OUT &&
					(chr_separator((*tokens)[i + 1].value, 0) == 0 ||
					ft_strlen((*tokens)[i + 1].value) > 2))
			(*tokens)[i + 1].type = TK_FILE_OUT;
		else if ((*tokens)[i + 1].value && (*tokens)[i].type == TK_APPEND &&
					(chr_separator((*tokens)[i + 1].value, 0) == 0 ||
					ft_strlen((*tokens)[i + 1].value) > 2))
			(*tokens)[i + 1].type = TK_FILE_APP;
		else if ((*tokens)[i + 1].value && (*tokens)[i].type == TK_HEREDOC &&
					(chr_separator((*tokens)[i + 1].value, 0) == 0 ||
					ft_strlen((*tokens)[i + 1].value) > 2))
			(*tokens)[i + 1].type = TK_EOF;
		i++;
	}
}

static void	ft_operators(t_token **tokens)
{
	int	i;
	int	receiver;

	i = -1;
	while ((*tokens)[++i].value != NULL)
	{
		if (ft_strlen((*tokens)[i].value) <= 2)
		{
			receiver = chr_separator((*tokens)[i].value, 0);
			assign_value(tokens, i, receiver);
		}
	}
}

void	ft_lexer(t_token **tokens)
{
	int	i;

	i = 0;
	if (*tokens == NULL)
		return ;
	while ((*tokens)[i].value != NULL)
	{
		(*tokens)[i].type = 0;
		i++;
	}
	ft_operators(tokens);
	ft_file_redir(tokens);
	ft_eof(tokens);
	ft_word_command_env(tokens);
}
