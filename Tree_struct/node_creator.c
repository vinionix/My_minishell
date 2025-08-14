/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/07/11 14:50:35 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_node(t_tree *node, int id)
{
	node->id_tree = id;
	node->left = NULL;
	node->right = NULL;
	node->subtree = NULL;
	node->prev = NULL;
	node->main = 0;
}

t_tree	*node_creator(t_token **tokens, int id)
{
	int		i;
	t_tree	*node;

	i = 0;
	while ((*tokens)[i].value && (*tokens)[i].id != id)
		i++;
	if ((*tokens)[i].value == NULL)
		return (NULL);
	node = (t_tree *)ft_calloc(1, sizeof(t_tree));
	node->type = (*tokens)[i].type;
	init_node(node, id);
	if ((*tokens)[i].type == TK_COMMAND || ((*tokens)[i].type >= TK_REDIR_IN
		&& (*tokens)[i].type <= TK_HEREDOC))
	{
		if ((*tokens)[i].type == TK_COMMAND)
			node->u_define.command.cmd = creat_command(id, (*tokens));
		node->u_define.command.list_redir = creat_list_redir(id, tokens);
		if (node->type == TK_COMMAND)
			creat_here_command(&node);
		else if (node->type != TK_COMMAND)
			here_verify(node->u_define.command.list_redir, 0);
	}
	else if ((*tokens)[i].type == TK_PIPE)
		node->u_define.pipe.std_in = -1;
	return (node);
}
