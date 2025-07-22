/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_exit_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:43:40 by gada-sil          #+#    #+#             */
/*   Updated: 2025/07/22 17:57:44 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

/* Só passar um itoa do exit_status aqui */

void    change_status(t_env *envs, char *status)
{
    t_env   *status_var;

    status_var = find_env("?=", envs);
    free(status_var->value);
    status_var->value = ft_strdup(status);
    free(status);
}