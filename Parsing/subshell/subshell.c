/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 23:07:59 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/22 18:53:04 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	redo_ids(t_token *tokens)
{
	int	i;

	i = -1;
	while (tokens[++i].value || tokens[i].type == TK_SUBSHELL)
		tokens[i].id = i;
}

static t_token	*remove_outter_paren(t_token *tokens, int i)
{
	t_token	*new;
	int		size;

	size = get_subshell_size(tokens, i);
	new = (t_token *)malloc(sizeof(t_token) * (size + 1));
	new[size].value = NULL;
	new[size].type = -1;
	copy_children(tokens, new, i, size);
	return (new);
}

static void	r_creat_subshell(t_token **new_tokens)
{
	int	i;

	i = 0;
	if (verify_paren(*new_tokens))
	{
		while ((*new_tokens)[i].value || (*new_tokens)[i].type == TK_SUBSHELL)
		{
			if ((*new_tokens)[i].type == TK_SUBSHELL)
				creat_subshell(&(*new_tokens)[i].subshell);
			i++;
		}
	}
}

void	creat_subshell(t_token **tokens)
{
	int		i;
	int		pos;
	t_token	*new_tokens;

	i = 0;
	pos = 0;
	new_tokens = size_new_tokens(*tokens);
	while ((*tokens)[i].value)
	{
		while ((*tokens)[i].value && (*tokens)[i].type != TK_INIT_PAREN)
			copy_token(new_tokens + pos++, (*tokens) + i++);
		if ((*tokens)[i].value && (*tokens)[i].type == TK_INIT_PAREN)
		{
			assign_subshell_token(new_tokens + pos, *tokens);
			new_tokens[pos++].subshell = remove_outter_paren(*tokens, i);
			skip_paren((*tokens), &i, 0);
		}
	}
	free_old_tokens(*tokens);
	*tokens = new_tokens;
	redo_ids(*tokens);
	r_creat_subshell(&new_tokens);
}
