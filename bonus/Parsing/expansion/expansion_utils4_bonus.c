/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils4_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:07:31 by gada-sil          #+#    #+#             */
/*   Updated: 2025/08/27 15:47:21 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_bonus.h"

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
