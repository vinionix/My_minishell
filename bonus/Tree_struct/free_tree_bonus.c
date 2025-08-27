/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/27 15:49:59 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	free_tree(t_tree *node)
{
	if (node == NULL)
		return ;
	free_tree(node->left);
	free_tree(node->right);
	if (node->type == TK_COMMAND || (node->type >= TK_REDIR_IN
			&& node->type <= TK_HEREDOC))
	{
		if (node->u_define.command.list_redir)
			free_list_redir(node->u_define.command.list_redir);
		if (node->u_define.command.cmd)
			free_matrix(node->u_define.command.cmd);
		free(node);
		return ;
	}
	if (node->type == TK_SUBSHELL)
		free_tree(node->subtree);
	free(node);
}

void	free_list(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		temp = env->next;
		if (env->value)
			free(env->value);
		if (env->key)
			free(env->key);
		free(env);
		env = temp;
	}
}
