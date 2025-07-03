/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:07:31 by gada-sil          #+#    #+#             */
/*   Updated: 2025/06/26 06:10:55 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static int	jump_to(char *str, char c, int i)
{
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	jump_to_smt_else(char *str, char c, int i)
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

static void	create_final_string(char **possibles, bool *matches,
			t_env *env, t_vars *var)
{
	char	*current_var;
	int		i;
	int		pos;
	char	*temp;

	i = -1;
	pos = 0;
	var->new_str = (char *)ft_calloc(1, var->final_len + 1);
	while (++i < ft_len_matrix(possibles))
	{
		while (var->copy[var->i] && var->copy[var->i] != POSSIBLE_ENV_MARKER)
			var->new_str[pos++] = var->copy[var->i++];
		if (matches[i])
		{
			current_var = ft_strjoin(possibles[i] + 1, "=");
			temp = find_env(current_var, env)->value;
			while (*temp)
				var->new_str[pos++] = *temp++;
			free(current_var);
		}
		var->i = jump_to_smt_else(var->copy, POSSIBLE_ENV_MARKER, var->i);
	}
	while (var->copy[var->i])
		var->new_str[pos++] = var->copy[var->i++];
}

static bool	*find_matches(char **matrix, t_env *env_lst, t_vars *var)
{
	t_env	*temp;
	bool	*matches;

	temp = env_lst;
	matches = (bool *)malloc(ft_len_matrix(matrix));
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

int	find_size(char *copy)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (copy[i])
	{
		i = jump_to(copy, POSSIBLE_ENV_MARKER, i);
		if (copy[i] && copy[i] == POSSIBLE_ENV_MARKER)
			size++;
		i = jump_to_smt_else(copy, POSSIBLE_ENV_MARKER, i);
	}
	return (size);
}

char	**create_possible_envs(char **matrix, char *str, char *copy)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = find_size(copy);
	matrix = (char **)malloc((size + 1) * sizeof(char *));
	size = 0;
	while (copy[i])
	{
		i = jump_to(copy, POSSIBLE_ENV_MARKER, i);
		if (!copy[i])
			break ;
		size = i;
		while (copy[size] == POSSIBLE_ENV_MARKER)
			size++;
		matrix[j++] = ft_substr(str, i, size - i);
		i = jump_to(copy, ' ', i);
	}
	matrix[j] = NULL;
	return (matrix);
}

static char	*mark_expansions(char *str)
{
	int		i;
	char	*copy;

	i = strchr_index_next(str, '$', 0);
	copy = ft_strdup((const char *)str);
	while (copy[i])
	{
		copy[i++] = POSSIBLE_ENV_MARKER;
		while (copy[i] && copy[i] != ' ' && copy[i] != '$'
			&& copy[i] != SINGLE_QUOTE_MARKER && copy[i] != DOUBLE_QUOTE_MARKER
				&& copy[i] != '\'' && copy[i] != '\"' && copy[i] != '*'
					&& copy[i] != '/' && copy[i] != ',')
			copy[i++] = POSSIBLE_ENV_MARKER;
		i = jump_to(copy, '$', i);
	}
	return (copy);
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

void	parse_edge_case(char **matrix)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (matrix[++i])
	{
		while (matrix[i][++j])
		{
			if (matrix[i][j] && matrix[i][j] == '$' && (matrix[i][j + 1] == ' '
				|| matrix[i][j + 1] == SINGLE_QUOTE_MARKER
					|| matrix[i][j + 1] == '\0'))
				matrix[i][j] = EXPANSION_MARKER;
		}
		j = -1;
	}
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
