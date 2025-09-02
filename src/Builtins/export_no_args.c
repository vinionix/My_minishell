/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 01:43:49 by gada-sil          #+#    #+#             */
/*   Updated: 2025/08/27 15:45:20 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../consha.h"

static int	is_unprintable(const char *key)
{
	if (!ft_strcmp(key, "?") || !ft_strcmp(key, "$"))
		return (1);
	return (0);
}

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
				&& !temp->printed && !is_unprintable(temp->key))
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
