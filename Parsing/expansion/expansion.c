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

char	*remove_dollar(char *str)
{
	char	*new;
	int		i;
	int		pos;
	size_t	size;

	size = ft_strlen(str);
	i = 0;
	pos = 0;
	while (str[i])
	{
		if (str[i++] == '$')
			size--;
	}
	i = 0;
	new = (char *)ft_calloc(1, size + 1);
	while (str[i])
	{
		if (str[i] != '$')
			new[pos++] = str[i];
		i++;
	}
	free(str);
	return (new);
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
		while (var->copy[var->i] && var->copy[var->i] != '$')
			var->new_str[pos++] = var->copy[var->i++];
		if (matches[i])
		{
			current_var = ft_strjoin(possibles[i] + 1, "=");
			temp = find_env(current_var, env)->value;
			while (*temp)
				var->new_str[pos++] = *temp++;
			free(current_var);
		}
		if (var->copy[var->i] && var->copy[var->i + 1] == '$')
		{
			var->i += 2;
			continue;
		}
		var->i = jump_to_smt_else(var->copy, '$', var->i);
		if (var->copy[var->i] == POSSIBLE_ENV_MARKER)
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

int	find_size(char *copy)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (copy[i])
	{
		if (copy[i++] == '$')
			size++;
	}
	i = 0;
	while (copy[i++])
	{
		if (copy[i] == '$' && copy[i + 1] == '$')
		{
			size--;
			i++;
		}
	}
	return (size);
}

void	fix_pid_and_status(int *i, char **matrix, int *j, char *str)
{
	if (str[*i + 1] == '$')
		matrix[(*j)++] = ft_strdup("$$");
	else
		matrix[(*j)++] = ft_strdup("$?");
	*i += 2;
	*i = jump_to(str, '$', *i);
	
}

void	create_envs(char *copy, char *str, int i, char **matrix)
{
	int	j;
	int	size;

	j = 0;
	size = 0;
	while (copy[i])
	{
		if (!copy[i])
			break ;
		if (str[i + 1] == '$' || str[i + 1] == '?')
		{
			fix_pid_and_status(&i, matrix, &j, str);
			continue ;
		}
		size = i + 1;
		if (copy[size] == EXPANSION_MARKER)
		{
			i++;
			continue;
		}
		while (copy[size] == POSSIBLE_ENV_MARKER)
			size++;
		matrix[j++] = ft_substr(str, i, size - i);
		i = jump_to(copy, '$', i + 1);
	}
}

char	**create_possible_envs(char **matrix, char *str, char *copy)
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

bool	check_meta(char c)
{
	return (c && c != ' ' && c != '$' && c != DOLLAR_MARKER
		&& c != SINGLE_QUOTE_MARKER && c != DOUBLE_QUOTE_MARKER
		&& c != '\'' && c != '\"' && c != '*'
		&& c != '/' && c != ',' && c != EXPANSION_MARKER
		&& c != '!' && c != '?' && c != '@' && c != '%'
		&& c != '&' && c != '+' && c != '-'
		&& c != '[' && c != ']' && c != '{'
		&& c != '}' && c != ';' && c != '.'
		&& c != '<' && c != '>' && c != '/'
		&& c != '~' && c != '|' && c != '=');
}

static char	*mark_expansions(char *str)
{
	int		i;
	char	*copy;

	i = jump_to(str, '$', 0);
	copy = ft_strdup((const char *)str);
	while (copy[i])
	{
		i++;
		if (copy[i] == '?' || copy[i] == '$')
		{
			copy[i] = POSSIBLE_ENV_MARKER;
			i++;
			i = jump_to(copy, '$', i);
			continue ;
		}
		while (check_meta(copy[i]))
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
			if (matrix[i][j] == '$' && matrix[i][j + 1] == '$')
			{
				j++;
				continue ;
			}
			if (matrix[i][j] == '$' && (matrix[i][j + 1] == ' '
				|| matrix[i][j + 1] == SINGLE_QUOTE_MARKER
				|| matrix[i][j + 1] == '\0' ||  matrix[i][j + 1] == '\"'
				|| matrix[i][j + 1] == '+' || matrix[i][j + 1] == '%'))
				matrix[i][j] = DOLLAR_MARKER;
			if (matrix[i][j] == '$' && matrix[i][j + 1] == '*')
				matrix[i][j + 1] = '1';
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
