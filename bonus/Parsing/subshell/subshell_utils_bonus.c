/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:36:34 by gada-sil          #+#    #+#             */
/*   Updated: 2025/08/27 15:47:48 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_bonus.h"

t_token	*size_new_tokens(t_token *tokens)
{
	int		i;
	int		final_size;
	t_token	*new_tokens;

	final_size = 0;
	i = 0;
	while (tokens[i].value != NULL)
	{
		while (tokens[i].value != NULL && tokens[i].type != TK_INIT_PAREN)
		{
			final_size++;
			i++;
		}
		if (tokens[i].type == TK_INIT_PAREN)
			skip_paren(tokens, &i, &final_size);
	}
	new_tokens = (t_token *)malloc(sizeof(t_token) * (final_size + 1));
	new_tokens[final_size].value = NULL;
	new_tokens[final_size].type = -1;
	return (new_tokens);
}

int	get_subshell_size(t_token *tokens, int i)
{
	int	init;
	int	final;
	int	size;

	init = 1;
	final = 0;
	size = 0;
	i++;
	while (final != init)
	{
		if (tokens[i].type == TK_INIT_PAREN)
			init++;
		else if (tokens[i].type == TK_FINAL_PAREN)
			final++;
		if (tokens[i].value)
			size++;
		i++;
	}
	return (size - 1);
}

void	free_old_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].value)
		free(tokens[i++].value);
	free(tokens);
}

bool	verify_paren(t_token *tokens)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tokens[i].value || tokens[i].type == TK_SUBSHELL)
	{
		if (tokens[i].type == TK_SUBSHELL)
		{
			while (tokens[i].subshell[j].value)
			{
				if (tokens[i].subshell[j].type == TK_INIT_PAREN)
					return (true);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (false);
}

void	skip_paren(t_token *tokens, int *i, int *final_size)
{
	int	init_paren;
	int	final_paren;

	if (final_size)
		(*final_size)++;
	final_paren = 0;
	init_paren = 1;
	(*i)++;
	while (final_paren != init_paren)
	{
		if (tokens[*i].type == TK_INIT_PAREN)
			init_paren++;
		else if (tokens[*i].type == TK_FINAL_PAREN)
			final_paren++;
		(*i)++;
	}
}
