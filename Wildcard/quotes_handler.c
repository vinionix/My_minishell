/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/06/25 20:34:08 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

static int	count_quotes_right(char *str, char c)
{
	int	i;
	int	size;

	i = -1;
	size = 0;
	while (str[++i])
	{
		if (str[i] == c)
			size++;
	}
	return (size);
}

static int	count_quotes_left(char *str, int i, char c)
{
	int	size;

	size = 0;
	while (i != -1)
	{
		if (str[i] == c)
			size++;
		i--;
	}
	return (size);
}

void parse_quotes(char **matrix, char c, char quote_type, char marker)
{
	int		i;
	int		index;
	int		start;

	i = -1;
	start = 0;
	while (matrix[++i])
	{
		if (matrix[i][0] == '\0')
			continue ;
		while (matrix[i][start])
		{
			index = strchr_index_next(matrix[i], c, start);
			if (count_quotes_right(matrix[i] + index, quote_type) % 2 != 0
					&& count_quotes_left(matrix[i], index, quote_type) % 2 != 0)
				matrix[i][index] = marker;
			if (matrix[i][index])
				start = index + 1;
			else
				break ;
		}
		start = 0;
		index = 0;
	}
}
