/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:19:40 by gada-sil          #+#    #+#             */
/*   Updated: 2025/08/26 16:25:46 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    print_error(char *error_message, char *token)
{
    if (token)
    {
        ft_putstr_fd(error_message, 2);
        ft_putstr_fd(" ´", 2);
        ft_putstr_fd(token, 2);
        ft_putstr_fd("'", 2);
        ft_putstr_fd("\n", 2);
        return ;
    }
    ft_putstr_fd(error_message, 2);
    ft_putstr_fd("\n", 2);
}