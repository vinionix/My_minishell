/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 00:44:20 by gada-sil          #+#    #+#             */
/*   Updated: 2025/08/28 15:24:14 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	write(1, "exit\n", 5);
	exit(exit_code);
}
