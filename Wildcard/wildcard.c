/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/05/16 04:06:53 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*update_vars(t_wildcard *list, const char *wildcard, t_var *var)
{
	char *str;

	str = NULL;
	list->index += var->size - var->start;
	var->start = var->size + 1;
	if (var->start - 1 < (unsigned int)ft_strlen(wildcard))
		var->size = strchr_index_next(wildcard, '*', var->start);
	str = ft_substr(wildcard, var->start, var->size - var->start);
	return (str);
}

static void	later_matches(t_wildcard *list, const char *wildcard, t_var *var)
{
	while (1337)
	{
		var->current_card = update_vars(list, wildcard, var);
		if (wildcard[var->start - 1] == '\0')
			return ;
		if (!ft_strstr(list->fileOrDir + list->index, var->current_card))
		{
			list->match = false;
			return ;
		}
		if (wildcard[list->index + (var->size - var->start) + 1 + var->ast] == '\0')
		{
			if (str_revcmp(list->fileOrDir + list->index,
				  (const char *)var->current_card))
			{
				list->match = false;
				return ;
			}
			return ;
		}
		free(var->current_card);
		var->current_card = NULL;
		var->ast++;
	}
}

static void	is_match(t_wildcard *list, const char *wildcard, t_var *var)
{
	var->current_card = ft_substr(wildcard, var->start, var->size - var->start);
	if (var->start == 0 && ft_strncmp(list->fileOrDir,
			(const char *)var->current_card, ft_strlen(var->current_card))
				&& wildcard[0] != '*')
	{
		list->match = false;
		return ;
	}
	free(var->current_card);
	var->current_card = NULL;
	later_matches(list, wildcard, var);
}

static int	parse_wildcard(t_wildcard *list,
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

const char	**wildcard(const char *wildcard)
{
	t_wildcard	*list;
	t_var		var;
	const char		**matches;

	list = NULL;
	init_vars(&var);
	read_current_dir(&list);
	parse_wildcard(list, wildcard, &var);
	matches = list_to_matrix(list);
	free_wildlist(&list);
	return (matches);
}
