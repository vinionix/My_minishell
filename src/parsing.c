/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 04:46:31 by gada-sil          #+#    #+#             */
/*   Updated: 2025/04/23 16:33:08 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_split(char **input)
{
    int i;
    
    i = 0;
	while (input[i])
    {
		free(input[i]);
        i++;
    }
	free(input);
}

void    parsing(const char *input)
{
    //int		i;
	char	**split;

    //i = 0;
	split = ft_split(input, ' ');

    free_split(split);
}