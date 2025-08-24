/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:40:21 by gada-sil          #+#    #+#             */
/*   Updated: 2025/08/22 18:54:47 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	copy_token(t_token *new, t_token *tokens)
{
	new->id = tokens->id;
	new->type = tokens->type;
	new->passed = tokens->passed;
	new->value = ft_strdup(tokens->value);
	new->subshell = tokens->subshell;
}

void	copy_children(t_token *tokens, t_token *new, int i, int size)
{
	i++;
	while (size--)
		copy_token(new++, tokens + i++);
}

void	assign_subshell_token(t_token *new, t_token *tokens)
{
	new->id = tokens->id;
	new->type = TK_SUBSHELL;
	new->value = NULL;
	new->passed = tokens->passed;
}
