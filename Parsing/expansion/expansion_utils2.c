/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:07:31 by gada-sil          #+#    #+#             */
/*   Updated: 2025/08/28 15:04:20 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int	jump_to(const char *str, char c, int i)
{
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	jump_to_smt_else(const char *str, char c, int i)
{
	if (str[i])
	{
		i++;
		while (str[i] && str[i] == c)
			i++;
	}
	return (i);
}

void	remove_key_len(char *copy, t_vars *var)
{
	int	i;

	i = -1;
	while (copy[++i])
	{
		if (copy[i] == POSSIBLE_ENV_MARKER)
			var->final_len--;
	}
}

bool	check_meta(char c)
{
	return (c && c != DOLLAR_MARKER
		&& c != SINGLE_QUOTE_MARKER && c != DOUBLE_QUOTE_MARKER
		&& !(c >= ' ' && c <= '/') && !(c >= ':' && c <= '@')
		&& !(c >= '[' && c <= '^') && !(c >= '{' && c <= '~'));
}
