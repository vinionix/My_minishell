/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:17:36 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/27 15:07:12 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_operators_final(t_token **tokens)
{
	int	i;

	i = 0;
	while ((*tokens)[++i].value != NULL)
	{
		if (((*tokens)[i + 1].value == NULL
			&& (*tokens)[i].type == TK_PIPE))
		{
			write(2, "Error\n", 7);
			return (1);
		}
	}
	return (0);
}

int	sintaxe_error(t_token **tokens)
{
	int	i;
	int	count_init_paren;
	int	count_final_paren;

	i = 0;
	count_init_paren = 0;
	count_final_paren = 0;
	while ((*tokens)[i].value != NULL)
	{
		if (check_first_token(tokens, i) || check_last_token(tokens, i)
			|| check_consecutive_operators(tokens, i))
			return (1);
		i++;
	}
	if (count_init_paren > count_final_paren)
	{
		write(2, "Error\n", 7);
		return (1);
	}
	return (check_operators_final(tokens));
}
