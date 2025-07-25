/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:38:02 by gada-sil          #+#    #+#             */
/*   Updated: 2024/09/25 12:09:55 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strstr(const char *big, const char *little)
{
	int		i;
	size_t	k;
	char	*str;

	i = 0;
	k = 0;
	str = (char *)big;
	if (big[i] == '\0')
		return (-1);
	if (little[k] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		k = 0;
		while ((str[i + k] == little[k]) || little[k] == '\0')
		{
			if (little[k] == '\0')
				return (i);
			k++;
		}
		i++;
	}
	return (i);
}
