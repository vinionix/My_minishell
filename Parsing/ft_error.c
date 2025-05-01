/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 03:51:03 by vfidelis          #+#    #+#             */
/*   Updated: 2025/05/01 05:55:48 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    sintaxe_error(t_token **tokens)
{
    int i;

    i = 0;
    while ((*tokens)[i].value != NULL)
    {
		if ((*tokens)[i].id == 0 && (*tokens)[i].type >= TK_PIPE && (*tokens)[i].type <= TK_OR)
		{
			printf("1 minishell: syntax error near unexpected token `%s'\n", (*tokens)[i].value);
			exit(1);
		}
		if ((*tokens)[i + 1].value == NULL && (*tokens)[i].type <= TK_HEREDOC)
		{
			printf("3 minishell: syntax error near unexpected token `newline'\n");
			exit(1);
		}
		if (i > 0 && (*tokens)[i].type <= TK_OR && (*tokens)[i - 1].type <= TK_OR)
		{
			printf("2 minishell: syntax error near unexpected token `%s'\n", (*tokens)[i].value);
			exit(1);
		}
		i++;
    }
}
