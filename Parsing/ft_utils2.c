/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:18:20 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/27 15:07:41 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	assign_value(t_token **tokens, int i, int receiver)
{
	if (receiver == 3)
		(*tokens)[i].type = TK_APPEND;
	else if (receiver == 4)
		(*tokens)[i].type = TK_HEREDOC;
	else if (receiver == 5)
		(*tokens)[i].type = TK_PIPE;
	else if (receiver == 6)
		(*tokens)[i].type = TK_REDIR_OUT;
	else if (receiver == 7)
		(*tokens)[i].type = TK_REDIR_IN;
}
