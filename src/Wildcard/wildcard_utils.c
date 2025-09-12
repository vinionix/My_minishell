#include "wildcard.h"

void	init_vars(t_var *vars)
{
	vars->start = 0;
	vars->size = 0;
	vars->current_card = NULL;
	vars->ast = 0;
}

int	str_revcmp(const char *s1, const char *s2)
{
	int	l1;
	int	l2;

	l1 = (int)ft_strlen(s1);
	l2 = (int)ft_strlen(s2);
	if ((l1 == 0 && l2 > 0) || (l2 == 0 && l1 > 0))
		return (1);
	while (l1 >= 0 && l2 >= 0)
	{
		if (s1[l1] != s2[l2])
			return (s1[l1] - s2[l2]);
		l1--;
		l2--;
	}
	if (l1 != l2 && l2 >= 0)
		return (s1[l1] - s2[l2]);
	return (0);
}

int	strchr_index_next(const char *str, char stop, unsigned int start)
{
	if (str[start])
		start++;
	while (str[start] && str[start] != stop)
		start++;
	return (start);
}

t_wildcard	*wild_lstnew(char *content)
{
	t_wildcard	*new_node;

	new_node = (t_wildcard *)malloc(sizeof(t_wildcard));
	if (!new_node)
		return (NULL);
	new_node->file_dir = content;
	new_node->match = true;
	if (is_hidden_file(content))
		new_node->is_hidden = true;
	else
		new_node->is_hidden = false;
	new_node->index = 0;
	new_node->next = (NULL);
	return (new_node);
}

void	wild_addback(t_wildcard **lst, t_wildcard *new)
{
	t_wildcard	*current;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

void	reset_matches(t_wildcard *list)
{
	while (list)
	{
		list->match = true;
		list->index = 0;
		list = list->next;
	}
}

char	*update_vars(const char *wildcard, t_var *var)
{
	char	*str;

	str = NULL;
	var->start = var->size + 1;
	if (var->start - 1 < (unsigned int)ft_strlen(wildcard))
		var->size = strchr_index_next(wildcard, '*', var->start);
	str = ft_substr(wildcard, var->start, var->size - var->start);
	return (str);
}

void	reset_modified_chars(char **matrix, char c)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (matrix[++i])
	{
		while (matrix[i][++j])
		{
			if (matrix[i][j] == DOLLAR_MARKER && c == '$')
				matrix[i][j] = c;
			else if (matrix[i][j] == EXPANSION_MARKER && c == '*')
				matrix[i][j] = c;
			else if (matrix[i][j] == SINGLE_QUOTE_MARKER && c == '\'')
				matrix[i][j] = '\'';
			else if (matrix[i][j] == DOUBLE_QUOTE_MARKER && c == '\"')
				matrix[i][j] = '\"';
		}
		j = -1;
	}
}

bool	edge_case(t_wildcard *list, const char *wildcard)
{
	char	*card;

	card = NULL;
	if (count_char(wildcard, '*') == 2 && wildcard[0] == '*'
		&& wildcard[ft_strlen(wildcard) - 1] == '*')
	{
		card = ft_substr(wildcard, 1, ft_strlen(wildcard) - 2);
		if (ft_strstr(list->file_dir, card))
		{
			free(card);
			return (true);
		}
		else
		{
			free(card);
			list->match = false;
			return (true);
		}
	}
	if (card)
		free(card);
	return (false);
}

bool	is_hidden_file(char *str)
{
	return (strchr_index(str, '.') == 0);
}

void	not_found(char **matrix, char *old_temp, int i)
{
	free(matrix[i]);
	matrix[i] = ft_strdup(old_temp);
	free(old_temp);
}

void	update(t_var *var, const char **temp, int *i, const char *wildcard)
{
	*i = strchr_index_next(wildcard, '*', *i);
	*temp = ft_strstr(*temp, var->current_card);
	*temp += ft_strlen(var->current_card);
	free(var->current_card);
	var->current_card = NULL;
	var->current_card = update_vars(wildcard, var);
}
