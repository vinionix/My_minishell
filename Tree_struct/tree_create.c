/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/05/16 04:06:53 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree	*tree_new(int type)
{
	t_tree	*new_node;

	new_node = (t_tree *)malloc(sizeof(t_tree));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	new_node->n_builtin = -1;
	new_node->right = NULL;
	new_node->left = NULL;
	return (new_node);
}

static void tree_add_left(t_tree **tree, t_tree *new)
{
	t_tree	*current;

	if (tree == NULL || new == NULL)
		return ;
	if (*tree == NULL)
	{
		*tree = new;
		return ;
	}
	current = *tree;
	while (current->left != NULL)
		current = current->left;
	current->left = new;
}

static int	final_pos_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while(tokens[i + 1].value != NULL)
		i++;
	return (i);
}
static void tree_init_left(t_token *tokens, t_tree **tree)
{
	int     i;
	int		id_token;

	id_token = TK_OR;
	i = final_pos_tokens(tokens);
	while (i >= 0)
	{
		if (tokens[i].type == id_token)
			tree_add_left(tree, tree_new(id_token));
		if (i == 0)
		{
			id_token--;
			i = final_pos_tokens(tokens);
		}
		i--;
	}
}

void    tree_creat(t_token *tokens)
{
}
