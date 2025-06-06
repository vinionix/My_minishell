/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:19:27 by vfidelis          #+#    #+#             */
/*   Updated: 2025/06/05 21:21:22 by vfidelis         ###   ########.fr       */
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

t_tree	*tree_left(t_token *tokens, int id)
{
	int	i;
	t_tree	*node;

	i = 0;
	while ((tokens)[i].value && (tokens)[i].id != id)
		i++;
	if ((tokens)[i].value == NULL)
		return(NULL);
	if ((tokens)[i].type == TK_COMMAND)
	{
		node = malloc(sizeof(t_tree));
		node->type = TK_COMMAND;
		node->u_define.command.command = creat_command(id, tokens);
		node->left = NULL;
		node->right = NULL;
		node->subtree = NULL;
		node->n_builtin = 0; //is_bultin(tokens);
	}
	//
}
void	tree_right(t_token *tokens, int id)
{
	
}