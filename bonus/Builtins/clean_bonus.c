/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 00:44:20 by gada-sil          #+#    #+#             */
/*   Updated: 2025/08/27 15:45:08 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	free_env_list(t_env *list)
{
	t_env	*temp;

	temp = list;
	while (temp)
	{
		temp = list->next;
		free(list->value);
		free(list->key);
		free(list);
		list = temp;
	}
}

void	ft_clean_and_exit(t_env *env, t_tree *tree, unsigned int exit_code)
{
	if (env)
		free_env_list(env);
	if (tree)
		free_tree(tree);
	exit(exit_code);
}
