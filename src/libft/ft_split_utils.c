/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:00:00 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/26 19:06:34 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../consha.h"

void	jump_index(int *index, size_t *size, const char *str)
{
	char	chr_jump;

	chr_jump = jump_char(str[*index]);
	if (chr_jump == 2 || chr_jump == 3)
	{
		(*index)++;
		(*size)++;
		while (str[*index] && chr_jump != jump_char(str[*index]))
		{
			(*index)++;
			(*size)++;
		}
	}
}

void	handle_jump(const char *s, int *i, char chr_jump)
{
	(*i)++;
	while (s[*i] && jump_char(s[*i]) != chr_jump)
		(*i)++;
}
