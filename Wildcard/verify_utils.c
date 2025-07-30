/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/06/12 16:12:34 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

bool	double_wildcard(const char *str)
{
	return (ft_strstr(str, "**") != NULL);
}

char	*compress_wildcards(char *str)
{
	int		i;
	int		size;
	char	*new;

	i = 0;
	size = 0;
	while (str[i])
	{
		size++;
		i = jump_to(str, '*', i);
		i = jump_to_smt_else(str, '*', i);
		i = jump_to(str, '*', i);
	}
	size += len_except(str, '*');
	new = (char *)ft_calloc(1, size + 1);
	reduce(str, new);
	return (new);
}

bool	check_sufix(t_wildcard *list, const char *wildcard)
{
	char	*card;

	card = NULL;
	if (wildcard[0] == '*' && count_char(wildcard, '*') == 1)
	{
		card = ft_substr(wildcard, 1, ft_strlen(wildcard) - 1);
		if (str_revcmp(list->file_dir, card))
		{
			free(card);
			list->match = false;
			return (true);
		}
		else
		{
			free(card);
			return (true);
		}
	}
	if (card)
		free(card);
	return (false);
}

int	count_char(const char *str, char c)
{
	int	size;

	size = 0;
	while (*str)
	{
		if (*str == c)
			size++;
		str++;
	}
	return (size);
}

bool	verify_ls_flag(char **matrix)
{
	if (matrix[0] && matrix[1])
		return (ft_strcmp(matrix[0], "ls") == 0 && ft_strchr(matrix[1], '-')
			&& ft_strchr(matrix[1], 'a'));
	return (false);
}
