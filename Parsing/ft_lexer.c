/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:49:33 by vfidelis          #+#    #+#             */
/*   Updated: 2025/04/28 04:53:17 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_

static void	ft_operators(t_token **tokens)
{
    int	i;
    int receiver;

	i = 0;
	while ((*tokens)[i].value != NULL)
	{
		if (ft_strlen((*tokens)[i].value) <= 2)
		{
			receiver = chr_separator((*tokens)[i].value, 0);
			if (receiver == 1)
				(*tokens)[i].type = TK_AND;
			else if (receiver == 2)
				(*tokens)[i].type = TK_OR;
			else if (receiver == 3)
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
		i++;
	}
}

void	ft_lexer(t_token **tokens)
{
	ft_operators(tokens);
}