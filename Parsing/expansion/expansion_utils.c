/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:07:31 by gada-sil          #+#    #+#             */
/*   Updated: 2025/08/28 15:03:51 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int	ft_strcmp_limited(char *s1, char *s2, char c)
{
	unsigned int	i;
	unsigned char	*s;

	i = 0;
	s = (unsigned char *)s1;
	while (s[i] != '\0' && s2[i] != '\0' && s[i] != c)
	{
		if (s[i] != s2[i])
			return (s[i] - s2[i]);
		i++;
	}
	if (s[i] == c && s2[i] == '\0')
		return (0);
	return (s[i] - s2[i]);
}

int	ft_strlen_until_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	key_size(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	return (i);
}

char	*join_strings(char *buffer, char *temp)
{
	char	*full;

	full = ft_strjoin(buffer, temp);
	if (buffer)
		free(buffer);
	return (full);
}
