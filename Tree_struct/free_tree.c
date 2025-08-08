/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/07/11 14:50:35 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tree(t_tree *node)
{
	if (node == NULL)
		return ;
	free_tree(node->left);
	free_tree(node->right);
	if (node->type == TK_COMMAND || (node->type >= TK_REDIR_IN
			&& node->type <= TK_HEREDOC))
	{
		if (node->u_define.command.cmd)
			free_matrix(node->u_define.command.cmd);
		free((char *)node->u_define.command.path);
		free(node);
		return ;
	}
	free(node);
}
