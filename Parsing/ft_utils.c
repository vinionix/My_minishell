/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 03:06:39 by vfidelis          #+#    #+#             */
/*   Updated: 2025/04/28 03:50:23 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	chr_separator(char *input, int i)
{
	if (input[i] == '&' && input[i + 1] == '&')
		return (1);
	else if (input[i] == '|' && input[i + 1] == '|')
		return (2);
	else if (input[i] == '>' && input[i + 1] == '>')
		return (3);
	else if (input[i] == '<' && input[i + 1] == '<')
		return (4);
	else if (input[i] == '|')
		return (5);
	else if (input[i] == '>')
		return (6);
	else if (input[i] == '<')
		return (7);
	return (0);
}

int	ft_len_matrix(char  **matrix)
{
    int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

int		jump_char(char chr)
{
	if (chr == ' ' || chr == '\t')
		return (1);
	if (chr == '"')
		return (2);
	if (chr == '\'')
		return (3);
	return (0);
}