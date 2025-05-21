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
	while (l1 >= 0 && l2 >= 0)
	{
		if (s1[l1] != s2[l2])
			return (s1[l1] - s2[l2]);
		l1--;
		l2--;
	}
	return (0);
}

int	strchr_index_next(const char *str, char stop, unsigned int start)
{
	while (str[start] && str[start] != stop)
		start++;
	return (start);
}

t_wildcard	*wild_lstnew(const char *content)
{
	t_wildcard	*new_node;

	new_node = (t_wildcard *)malloc(sizeof(t_wildcard));
	if (!new_node)
		return (NULL);
	new_node->fileOrDir = content;
	new_node->match = true;
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
