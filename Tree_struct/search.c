/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/27 15:24:16 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	final_pos_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i + 1].value != NULL)
		i++;
	return (i);
}

void	verify_tokens_right(t_token **tokens, int i, int *flag, int *receiver)
{
	if ((*tokens)[i].type == TK_PIPE && (*flag) != 2 && (*flag) != 3)
	{
		(*flag) = 3;
		(*receiver) = i;
	}
	else if ((*tokens)[i].type == TK_COMMAND && (*flag) != 2 && (*flag) != 3
		&& (*flag) != 4)
	{
		(*flag) = 4;
		(*receiver) = i;
	}
	else if ((*tokens)[i].type >= TK_REDIR_IN
		&& (*tokens)[i].type <= TK_HEREDOC
		&& (*flag) != 2 && (*flag) != 3 && (*flag) != 4
		&& (*flag) != 5)
	{
		(*flag) = 5;
		(*receiver) = i;
	}
}

int	find_next_r(t_token **tokens, int start, int receiver, int flag)
{
	int	i;

	i = start;
	while (((*tokens)[i].value)
		&& (*tokens)[i].passed == -1)
	{
		verify_tokens_right(tokens, i, &flag, &receiver);
		i++;
	}
	return (receiver);
}

int	search_left(t_token **tokens, int id)
{
	int	i;
	int	flag;
	int	receiver;

	i = 0;
	flag = -1;
	receiver = 0;
	while (((*tokens)[i].value)
		&& (*tokens)[i].id != id)
		i++;
	i--;
	while (i >= 0 && (*tokens)[i].passed != 1)
	{
		check_priority(tokens, i, &receiver, &flag);
		i--;
	}
	if ((*tokens)[receiver].passed == 1)
		return (-1);
	(*tokens)[receiver].passed = 1;
	return ((*tokens)[receiver].id);
}

int	search_right(t_token **tokens, int id)
{
	int	i;
	int	receiver;

	i = 0;
	while (((*tokens)[i].value)
		&& (*tokens)[i].id != id)
		i++;
	if ((*tokens)[i + 1].value != NULL)
		i++;
	receiver = find_next_r(tokens, i, -1, -1);
	if (receiver == -1 || (*tokens)[receiver].passed == 1)
		return (-1);
	(*tokens)[receiver].passed = 1;
	return ((*tokens)[receiver].id);
}

t_tree	*search_for_bigger(t_token **tokens)
{
	int	i;
	int	flag;
	int	receiver;

	if (!tokens || !*tokens)
		return (NULL);
	i = final_pos_tokens((*tokens));
	flag = 0;
	receiver = 0;
	while (i >= 0)
	{
		check_priority(tokens, i, &receiver, &flag);
		i--;
	}
	(*tokens)[receiver].passed = 1;
	return (node_creator(tokens, (*tokens)[receiver].id, 0));
}
