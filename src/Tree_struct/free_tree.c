/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/28 15:06:27 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../consha.h"

void	free_tree(t_tree *node)
{
	if (!node)
		return ;
	if (node->left)
		free_tree(node->left);
	if (node->right)
		free_tree(node->right);
	if (node && node->type == TK_COMMAND)
	{
		if (node && node->u_define.command.cmd)
			free_matrix(node->u_define.command.cmd);
		if (node && node->u_define.command.list_redir)
			free_list_redir(node->u_define.command.list_redir);
	}
	else if (node && node->type >= TK_REDIR_IN && node->type <= TK_HEREDOC)
	{
		if (node && node->u_define.command.list_redir)
			free_list_redir(node->u_define.command.list_redir);
	}
	else if (node && node->type == TK_SUBSHELL)
		free_tree(node->subtree);
	if (node)
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
