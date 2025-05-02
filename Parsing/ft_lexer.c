/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:49:33 by vfidelis          #+#    #+#             */
/*   Updated: 2025/05/01 23:08:04 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_word_command_env(t_token **tokens)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*tokens)[i].value != NULL)
	{
		if ((*tokens)[i].type == 0)
		{
			if ((*tokens)[i].id == 0 || ((*tokens)[i - 1].type >= TK_PIPE && 
				(*tokens)[i - 1].type <= TK_OR))
				(*tokens)[i].type = TK_COMMAND;
			else
				(*tokens)[i].type = TK_WORD;
		}
		i++;
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
    int receiver;

	i = 0;
	while ((*tokens)[i].value != NULL)
	{
		if (ft_strlen((*tokens)[i].value) <= 2)
		{
			receiver = chr_separator((*tokens)[i].value, 0);
			if (receiver == 1)
				(*tokens)[i].type = TK_AND;
			else if (receiver == 2)
				(*tokens)[i].type = TK_OR;
			else if (receiver == 3)
				(*tokens)[i].type = TK_APPEND;
			else if (receiver == 4)
				(*tokens)[i].type = TK_HEREDOC;
			else if (receiver == 5)
				(*tokens)[i].type = TK_PIPE;
			else if (receiver == 6)
				(*tokens)[i].type = TK_REDIR_OUT;
			else if (receiver == 7)
				(*tokens)[i].type = TK_REDIR_IN;
		}
		i++;
	}
}

void	ft_lexer(t_token **tokens)
{
	ft_operators(tokens);
	ft_file_redir(tokens);
	ft_eof(tokens);
	ft_word_command_env(tokens);
}