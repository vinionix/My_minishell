/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/06/25 20:37:54 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

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
