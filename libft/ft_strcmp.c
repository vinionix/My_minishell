/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:38:02 by gada-sil          #+#    #+#             */
/*   Updated: 2024/09/25 12:09:55 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;
	unsigned char	*s;

	i = 0;
	s = (unsigned char *)s1;
	while (s[i] != '\0' && s2[i] != '\0')
	{
		if (s[i] != s2[i])
			return (s[i] - s2[i]);
		i++;
	}
	return (s[i] - s2[i]);
}
