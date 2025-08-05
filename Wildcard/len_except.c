/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_except.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/07/22 17:55:01 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	reduce(const char *str, char *new)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '*')
			new[size++] = str[i++];
		if (str[i])
			new[size++] = '*';
		i = jump_to_smt_else(str, '*', i);
	}
}

int	len_except(const char *str, char exception)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i++] != exception)
			len++;
	}
	return (len);
}
