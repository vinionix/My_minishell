/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 01:43:49 by gada-sil          #+#    #+#             */
/*   Updated: 2025/08/27 19:13:07 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	tk_and(t_tree *current_node)
{
	if (current_node->left->type == TK_SUBSHELL)
		exec_subshell(current_node->left->subtree);
	else if (current_node->left->type == TK_COMMAND)
		exec_command_solo(current_node->left);
	else if (current_node->left->type >= TK_REDIR_IN
		&& current_node->left->type <= TK_HEREDOC)
		creat_solo_redirect(current_node->left->u_define.command.list_redir);
	if (current_node->right->type == TK_SUBSHELL && get_data()->exit_code == 0)
		exec_subshell(current_node->right->subtree);
	else if (current_node->right->type == TK_PIPE && get_data()->exit_code == 0)
		ft_pipe(&current_node->right, 0);
	else if (current_node->right->type == TK_COMMAND
		&& get_data()->exit_code == 0)
		exec_command_solo(current_node->right);
	else if (current_node->right->type >= TK_REDIR_IN
		&& current_node->right->type <= TK_HEREDOC
		&& get_data()->exit_code == 0)
		creat_solo_redirect(current_node->right->u_define.command.list_redir);
}

void	tk_or(t_tree *current_node)
{
	if (current_node->left->type == TK_SUBSHELL)
		exec_subshell(current_node->left->subtree);
	else if (current_node->left->type == TK_COMMAND)
		exec_command_solo(current_node->left);
	else if (current_node->left->type >= TK_REDIR_IN
		&& current_node->left->type <= TK_HEREDOC)
		creat_solo_redirect(current_node->left->u_define.command.list_redir);
	if (current_node->right->type == TK_SUBSHELL && get_data()->exit_code != 0)
		exec_subshell(current_node->right->subtree);
	else if (current_node->right->type == TK_PIPE && get_data()->exit_code != 0)
		ft_pipe(&current_node->right, 0);
	else if (current_node->right->type == TK_COMMAND
		&& get_data()->exit_code != 0)
		exec_command_solo(current_node->right);
	else if (current_node->right->type >= TK_REDIR_IN
		&& current_node->right->type <= TK_HEREDOC
		&& get_data()->exit_code != 0)
		creat_solo_redirect(current_node->right->u_define.command.list_redir);
}
