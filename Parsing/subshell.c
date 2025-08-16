/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 23:07:59 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/16 05:22:13 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_paren(t_token *tokens, int *i, int *final_size)
{
	int	init_paren;
	int	final_paren;
	
	final_paren = 0;
	init_paren = 0;
	if (tokens[*i].type == TK_INIT_PAREN)
	{
		init_paren++;
		(*i)++;
		while (final_paren != init_paren)
		{
			if (tokens[*i].type == TK_INIT_PAREN)
			{
				init_paren++;
				(*final_size)++;
			}
			else if (tokens[*i].type == TK_FINAL_PAREN)
				final_paren++;
		(*i)++;
		}
	}
}

t_token	*size_new_tokens(t_token *tokens)
{
	int	i;
	int	final_size;
	t_token	*new_tokens;

	i = 0;
	final_size = 0;
	while (tokens[i].value != NULL)
	{
		if (tokens[i].type == TK_INIT_PAREN)
			skip_paren(tokens, &i, &final_size);
		i++;
		if (tokens[i].type != TK_FINAL_PAREN)
			final_size++;
	}
	new_tokens = (t_token *)malloc(sizeof(t_token) * (final_size + 1));
	return (new_tokens);
}

void    creat_subshell(t_token **tokens)
{
    int i;
	t_token	*new_tokens;
    i = 0;

	new_tokens = size_new_tokens((*tokens));
    while ((*tokens)[i].value)
	{
		if ((*tokens)[i].type == TK_INIT_PAREN)
		{
			
		}
	}
}