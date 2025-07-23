/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:43:40 by gada-sil          #+#    #+#             */
/*   Updated: 2025/07/22 17:57:44 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

/* Só passar um itoa do exit_status aqui */

void    change_env_var(t_env *envs, char *env_to_change, char *value)
{
    t_env   *env;

    env = find_env(env_to_change, envs);
    free(env->value);
    env->value = ft_strdup(value);
}
