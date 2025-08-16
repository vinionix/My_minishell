/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 03:51:03 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/14 18:09:58 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_first_token(t_token **tokens, int i)
{
	if ((*tokens)[i].id == 0 && (*tokens)[i].type >= TK_PIPE
		&& (*tokens)[i].type <= TK_FINAL_PAREN)
	{
		printf("minishell: syntax error near unexpected token `%s'\n",
			(*tokens)[i].value);
		return (1);
	}
	return (0);
}

static int	check_last_token(t_token **tokens, int i)
{
	if ((*tokens)[i + 1].value == NULL && (*tokens)[i].type <= TK_HEREDOC)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

static int	check_consecutive_operators(t_token **tokens, int i)
{
	if (i > 0 && ((*tokens)[i].type >= TK_PIPE
		&& (*tokens)[i].type <= TK_FINAL_PAREN) && ((*tokens)[i
			- 1].type >= TK_PIPE && (*tokens)[i - 1].type <= TK_OR))
	{
		printf("minishell: syntax error near unexpected token `%s'\n",
			(*tokens)[i].value);
		return (1);
	}
	return (0);
}

static int	check_init_paren(t_token **tokens, int i, int *count_init_paren)
{
	if ((*tokens)[i].type == TK_INIT_PAREN)
	{
		(*count_init_paren)++;
		if ((i > 0 && (*tokens)[i + 1].value == NULL && (*tokens)[i
			- 1].type >= TK_FILE_IN) || ((*tokens)[i
				- 1].type >= TK_REDIR_IN && (*tokens)[i - 1].type <= TK_HEREDOC)
			|| ((*tokens)[i + 1].type == TK_FINAL_PAREN))
		{
			printf("minishell: syntax error near unexpected token `%s'\n",
				(*tokens)[i + 1].value);
			return (1);
		}
	}
	return (0);
}

static int	check_final_paren(t_token **tokens, int i, int *count_final_paren,
		int count_init_paren)
{
	if ((*tokens)[i].type == TK_FINAL_PAREN)
	{
		(*count_final_paren)++;
		if (*count_final_paren > count_init_paren)
		{
			printf("minishell: syntax error near unexpected token `)'\n");
			return (1);
		}
	}
	return (0);
}

int	check_operators_final(t_token **tokens)
{
	int	i;

	i = 0;
	while ((*tokens)[++i].value != NULL)
	{
		if (((*tokens)[i + 1].value == NULL
				&& (*tokens)[i].type >= TK_PIPE && (*tokens)[i].type <= TK_OR))
		{
			printf("Error\n");
			return (1);
		}
	}
	return (0);
}

int	sintaxe_error(t_token **tokens)
{
	int	i;
	int	count_init_paren;
	int	count_final_paren;

	i = 0;
	count_init_paren = 0;
	count_final_paren = 0;
	while ((*tokens)[i].value != NULL)
	{
		if (check_first_token(tokens, i) || check_last_token(tokens, i)
			|| check_consecutive_operators(tokens, i)
			|| check_init_paren(tokens, i, &count_init_paren)
			|| check_final_paren(tokens, i, &count_final_paren,
				count_init_paren))
			return (1);
		i++;
	}
	if (count_init_paren > count_final_paren)
	{
		printf("Error\n");
		return (1);
	}
	return (check_operators_final(tokens));
}
