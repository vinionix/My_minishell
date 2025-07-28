/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/06/25 20:36:29 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

static void	later_matches(t_wildcard *list, const char *wildcard, t_var *var)
{
	const char	*temp;
	int			i;

	temp = list->file_dir;
	i = 0;
	while (1337)
	{
		if (!*var->current_card)
			return ;
		if (!ft_strstr(temp, var->current_card))
		{
			list->match = false;
			return ;
		}
		if (wildcard[i + ft_strlen(var->current_card) + 1] == '\0')
		{
			if (str_revcmp(temp, (const char *)var->current_card))
			{
				list->match = false;
				return ;
			}
		}
		i = strchr_index_next(wildcard, '*', i);
		temp = ft_strstr(temp, var->current_card);
		temp += ft_strlen(var->current_card);
		free(var->current_card);
		var->current_card = NULL;
		var->current_card = update_vars(wildcard, var);
	}
}

static void	is_match(t_wildcard *list, const char *wildcard, t_var *var)
{
	if (wildcard[0] == '*')
		var->start = 1;
	var->current_card = ft_substr(wildcard, var->start, var->size - var->start);
	if (var->start == 0 && ft_strncmp(list->file_dir,
			(const char *)var->current_card, ft_strlen(var->current_card))
		&& wildcard[0] != '*')
	{
		list->match = false;
		return ;
	}
	if (count_char(wildcard, '*') == 1
			&& wildcard[strchr_index(wildcard, '*') + 1] == '\0')
		return ;
	if (check_sufix(list, wildcard))
		return ;
	if (edge_case(list, wildcard))
		return ;
	later_matches(list, wildcard, var);
}

static int	expand_wildcard(t_wildcard *list,
				const char *wildcard, t_var *var)
{
	t_wildcard		*temp;

	temp = list;
	while (temp)
	{
		var->size = strchr_index_next(wildcard, '*', var->start);
		is_match(temp, wildcard, var);
		free(var->current_card);
		var->current_card = NULL;
		init_vars(var);
		temp = temp->next;
	}
	return (0);
}

static char	**wildcard_aux(char **matrix, t_wildcard *list,
			t_var *var, bool show_hidden)
{
	int		i;
	char	**matches;

	i = -1;
	matches = NULL;
	while (matrix[++i])
	{
		if (have_char(matrix[i], '*') && double_wildcard(matrix[i]))
		{
			expand_wildcard(list, matrix[i], var);
			matches = list_to_matrix(list, show_hidden);
			if (!matches)
				continue ;
			matrix = join_matrices(matrix, matches, i);
			reset_matches(list);
		}
	}
	return (matrix);
}

char	**wildcard(char **matrix)
{
	t_wildcard	*list;
	t_var		var;

	list = NULL;
	init_vars(&var);
	read_current_dir(&list);
	matrix = wildcard_aux(matrix, list, &var, verify_ls_flag(matrix));
	free_wildlist(&list);
	return (matrix);
}
