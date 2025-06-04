/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:49:33 by vfidelis          #+#    #+#             */
/*   Updated: 2025/06/04 17:59:01 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_word_command_env(t_token **tokens)
{
	int	i;

	i = 0;
	while ((*tokens)[i].value != NULL)
	{
		if ((*tokens)[i].type == 0)
		{
			if ((*tokens)[i].id == 0 || ((*tokens)[i - 1].type >= TK_PIPE
					&& (*tokens)[i - 1].type <= TK_OR))
				{
					(*tokens)[i].type = TK_COMMAND;
					(*tokens)[i].id = (*tokens)[i].id * 10;
				}
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
	int	receiver;

	i = -1;
	while ((*tokens)[++i].value != NULL)
	{
		if (ft_strlen((*tokens)[i].value) <= 2)
		{
			receiver = chr_separator((*tokens)[i].value, 0);
			if (receiver == 1)
			{
				(*tokens)[i].type = TK_AND;
				(*tokens)[i].id = (*tokens)[i].id * 1000;
			}
			else if (receiver == 2)
			{
				(*tokens)[i].type = TK_OR;
				(*tokens)[i].id = (*tokens)[i].id * 1000;
			}
			else if (receiver == 3)
			{
				(*tokens)[i].type = TK_APPEND;
				(*tokens)[i].id = (*tokens)[i].id * 100;
			}
			else if (receiver == 4)
			{
				(*tokens)[i].type = TK_HEREDOC;
				(*tokens)[i].id = (*tokens)[i].id * 100;
			}
			else if (receiver == 5)
			{
				(*tokens)[i].type = TK_PIPE;
				(*tokens)[i].id = (*tokens)[i].id * 100;
			}
			else if (receiver == 6)
			{
				(*tokens)[i].type = TK_REDIR_OUT;
				(*tokens)[i].id = (*tokens)[i].id * 100;				
			} 
			else if (receiver == 7)
			{
				(*tokens)[i].type = TK_REDIR_IN;
				(*tokens)[i].id = (*tokens)[i].id * 100;
			}
			else if (receiver == 8)
				(*tokens)[i].type = TK_INIT_PAREN;
			else if (receiver == 9)
			(*tokens)[i].type = TK_FINAL_PAREN;
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
