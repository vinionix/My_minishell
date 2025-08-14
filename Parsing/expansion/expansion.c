/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:07:31 by gada-sil          #+#    #+#             */
/*   Updated: 2025/08/12 22:27:32 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static void	create_final_string(char **possibles, bool *matches,
			t_env *env, t_vars *var)
{
	int	pos;

	var->new_str = (char *)ft_calloc(1, var->final_len + 1);
	pos = create_string(possibles, matches, env, var);
	while (var->copy[var->i])
		var->new_str[pos++] = var->copy[var->i++];
}

static bool	*find_matches(char **matrix, t_env *env_lst, t_vars *var)
{
	t_env	*temp;
	bool	*matches;

	temp = env_lst;
	matches = (bool *)ft_calloc(ft_len_matrix(matrix), 1);
	while (matrix[++var->i])
	{
		while (temp)
		{
			if (!ft_strcmp(matrix[var->i] + 1, temp->key))
			{
				var->final_len += (int)ft_strlen(temp->value);
				matches[var->i] = true;
				break ;
			}
			matches[var->i] = false;
			temp = temp->next;
		}
		temp = env_lst;
	}
	return (matches);
}

static char	**create_possible_envs(char **matrix, char *str, char *copy)
{
	int	i;
	int	size;

	i = 0;
	size = find_size(copy);
	matrix = (char **)ft_calloc((size + 1) * sizeof(char *), 1);
	while (size != -1)
		matrix[size--] = NULL;
	i = jump_to(copy, '$', i);
	create_envs(copy, str, i, matrix);
	return (matrix);
}

static char	*expand(char *str, t_env *env_lst)
{
	char	**possibles;
	char	*copy;
	t_vars	var;
	bool	*matches_pos;

	possibles = NULL;
	matches_pos = NULL;
	var.i = -1;
	copy = mark_expansions(str);
	var.final_len = (int)ft_strlen(copy);
	var.copy = copy;
	possibles = create_possible_envs(possibles, str, copy);
	matches_pos = find_matches(possibles, env_lst, &var);
	remove_key_len(copy, &var);
	var.i = 0;
	create_final_string(possibles, matches_pos, env_lst, &var);
	free_matrix(possibles);
	free(copy);
	free(str);
	free(matches_pos);
	return (var.new_str);
}

void	expand_variables(char **matrix, t_env *env_lst)
{
	int	i;

	i = 0;
	parse_edge_case(matrix);
	while (matrix[i])
	{
		if (have_char(matrix[i], '$'))
			matrix[i] = expand(matrix[i], env_lst);
		i++;
	}
}
