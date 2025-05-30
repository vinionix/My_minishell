/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/05/30 02:36:51 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_redirs(t_token_type type, t_token *token, t_tree *new_node)
{
	if (TK_REDIR_IN == type)
	{
		
	}
}

void	set_type(t_token *tokens, t_tree *new_node, int type)
{
	if (type >= TK_REDIR_IN && type <= TK_HEREDOC)
		ft_redirs(type, token, new_node);
	else if (type == TK_OR)
		ft_memset(&new_node->u_define.or, 0, sizeof(new_node->u_define.or));
	else if (type == TK_COMMAND)
		ft_memset(&new_node->u_define.command, 0,
			sizeof(new_node->u_define.command));
	else if (type == TK_PIPE)
		ft_memset(&new_node->u_define.pipe, 0, sizeof(new_node->u_define.pipe));
}

t_tree	*tree_new(t_token *token, int type)
{
	t_tree	*new_node;

	new_node = (t_tree *)malloc(sizeof(t_tree));
	if (!new_node)
		return (NULL);
	set_type(new_node, type);
	
	new_node->right = NULL;
	new_node->left = NULL;
	return (new_node);
}

int	final_pos_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i + 1].value != NULL)
		i++;
	return (i);
}