#include "expansion.h"

int	ft_strcmp_limited(char *s1, char *s2, char c)
{
	unsigned int	i;
	unsigned char	*s;

	i = 0;
	s = (unsigned char *)s1;
	while (s[i] != '\0' && s2[i] != '\0' && s[i] != c)
	{
		if (s[i] != s2[i])
			return (s[i] - s2[i]);
		i++;
	}
	if (s[i] == c && s2[i] == '\0')
		return (0);
	return (s[i] - s2[i]);
}

int	ft_strlen_until_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	key_size(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	return (i);
}

char	*join_strings(char *buffer, char *temp)
{
	char	*full;

	full = ft_strjoin(buffer, temp);
	if (buffer)
		free(buffer);
	return (full);
}

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
	return (c && c != EXPANSION_MARKER && c != DOLLAR_MARKER
		&& c != SINGLE_QUOTE_MARKER && c != DOUBLE_QUOTE_MARKER
		&& !(c >= ' ' && c <= '/') && !(c >= ':' && c <= '@')
		&& !(c >= '[' && c <= '^') && !(c >= '{' && c <= '~'));
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
				|| matrix[i][j + 1] == '\0' || matrix[i][j + 1] == '\"'
				|| matrix[i][j + 1] == '+' || matrix[i][j + 1] == '%'))
				matrix[i][j] = DOLLAR_MARKER;
			if (matrix[i][j] == '$' && matrix[i][j + 1] == '*')
				matrix[i][j + 1] = '1';
		}
		j = -1;
	}
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
			continue ;
		}
		while (copy[size] == POSSIBLE_ENV_MARKER)
			size++;
		matrix[j++] = ft_substr(str, i, size - i);
		i = jump_to(copy, '$', i + 1);
	}
}

char	*mark_expansions(char *str)
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

bool	jump_dollar(t_vars *var)
{
	if (var->copy[var->i] && var->copy[var->i + 1] == '$')
	{
		var->i += 2;
		return (true);
	}
	return (false);
}

void	copy(t_vars *var, int *pos)
{
	while (var->copy[var->i] && var->copy[var->i] != '$')
		var->new_str[(*pos)++] = var->copy[var->i++];
}

int	create_string(char **possibles, bool *matches, t_env *env, t_vars *var)
{
	char	*current_var;
	int		i;
	int		pos;
	char	*temp;

	i = -1;
	pos = 0;
	while (++i < ft_len_matrix(possibles))
	{
		copy(var, &pos);
		if (matches[i])
		{
			current_var = ft_strjoin(possibles[i] + 1, "=");
			temp = find_env(current_var, env)->value;
			while (*temp)
				var->new_str[pos++] = *temp++;
			free(current_var);
		}
		if (jump_dollar(var))
			continue ;
		var->i = jump_to_smt_else(var->copy, '$', var->i);
		if (var->copy[var->i] == POSSIBLE_ENV_MARKER)
			var->i = jump_to_smt_else(var->copy, POSSIBLE_ENV_MARKER, var->i);
	}
	return (pos);
}
