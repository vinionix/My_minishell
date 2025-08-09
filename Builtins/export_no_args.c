/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 01:43:49 by gada-sil          #+#    #+#             */
/*   Updated: 2025/05/15 22:18:08 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	reset_prints(t_env *envs)
{
	while (envs)
	{
		envs->printed = false;
		envs = envs->next;
	}
}

static void	print(t_env *to_print)
{
	if (to_print)
	{
		printf("declare -x %s=\"%s\"\n", to_print->key, to_print->value);
		to_print->printed = true;
	}
}

int	export_no_args(t_env *envs)
{
	t_env	*temp;
	t_env	*to_print;
	bool	all_printed;

	all_printed = false;
	while (!all_printed)
	{
		temp = envs;
		to_print = NULL;
		all_printed = true;
		while (temp)
		{
			if ((!to_print || ft_strcmp(temp->key, to_print->key) < 0)
				&& !temp->printed)
			{
				to_print = temp;
				all_printed = false;
			}
			temp = temp->next;
		}
		print(to_print);
	}
	reset_prints(envs);
	return (0);
}
