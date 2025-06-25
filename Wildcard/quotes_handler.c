/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   by: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   updated: 2025/06/12 16:12:33 by gada-sil         ###   ########.fr       */
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

void parse_quotes(char **matrix, char c)
{
	int		i;
	int		index;
	int		start;

	i = 0;
	start = 0;
	while (matrix[++i])
	{
		if (matrix[i][0] == '\0')
			continue ;
		while (matrix[i][start])
		{
			index = strchr_index_next(matrix[i], '*', start);
			if (matrix[i][index] == '\0') /* talvez de merda kk tem que testar mais*/
			{
				start = 0;
				index = 0;
				break ;
			}
			if (count_quotes_right(matrix[i] + index, c) % 2 != 0
					&& count_quotes_left(matrix[i] + index, index, c) % 2 != 0)
				matrix[i][index] = WILDCARD_MARKER;
			start = index + 1;
		}
	}
}
