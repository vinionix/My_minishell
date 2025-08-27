/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 01:43:49 by gada-sil          #+#    #+#             */
/*   Updated: 2025/08/27 15:45:23 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	ft_unset(char **matrix, t_env **envs)
{
	int	i;

	i = 0;
	while (matrix[++i] != NULL)
		unset_env_if(envs, matrix[i]);
	return (0);
}
