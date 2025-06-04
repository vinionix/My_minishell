/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 03:51:03 by vfidelis          #+#    #+#             */
/*   Updated: 2025/05/26 13:13:32 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	sintaxe_error(t_token **tokens)
{
	int	i;
	int	count_init_paren;
	int count_final_paren;

	i = 0;
	count_init_paren = 0;
	count_final_paren = 0;
	while ((*tokens)[i].value != NULL)
	{
		if ((*tokens)[i].id == 0 && (*tokens)[i].type >= TK_PIPE
			&& (*tokens)[i].type <= TK_FINAL_PAREN)
		{
			printf("minishell: syntax error near unexpected token `%s'\n",
				(*tokens)[i].value);
			return (1);
		}
		if ((*tokens)[i + 1].value == NULL && (*tokens)[i].type <= TK_HEREDOC)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (1);
		}
		if (i > 0 && (*tokens)[i].type <= TK_OR && (*tokens)[i
			- 1].type <= TK_OR)
		{
			printf("minishell: syntax error near unexpected token `%s'\n",
				(*tokens)[i].value);
				return (1);
		}
		if ((*tokens)[i].type == TK_INIT_PAREN)
		{
			count_init_paren++;
			if ((i > 0 && (*tokens)[i + 1].value != NULL && (*tokens)[i - 1].type >= TK_FILE_IN)|| 
				((*tokens)[i - 1].type >= TK_REDIR_IN && 
					(*tokens)[i - 1].type <= TK_HEREDOC) || ((*tokens)[i + 1].type == TK_FINAL_PAREN))
			{
				printf("minishell: syntax error near unexpected token `%s'\n",
					(*tokens)[i + 1].value);
				return (1);
			}
		}
		if ((*tokens)[i].type == TK_FINAL_PAREN)
		{
			count_final_paren++;
			if (count_final_paren > count_init_paren)
			{
				printf("minishell: syntax error near unexpected token `)'\n");
				return (1);
			}
		}
		i++;
	}
	if (count_init_paren > count_final_paren)
	{
		printf("Error\n");
		return (1);
	}
	return (0);
}
