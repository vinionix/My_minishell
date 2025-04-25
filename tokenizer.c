/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:39:07 by vfidelis          #+#    #+#             */
/*   Updated: 2025/04/24 23:18:29 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		jump_char(char chr)
{
	if (chr == ' ' || chr == '\t')
		return (1);
	if (chr == '"')
		return (2);
	if (chr == '\'')
		return (3);
	return (0);
}
int	skip_space(char *input, int i)
{
	while(jump_char(input[i]) == 1)
		i++;
	return (i);
}

int	chr_separator(char *input, int i)
{
	if (input[i] == '&' && input[i + 1] == '&')
		return (1);
	else if (input[i] == '|' && input[i + 1] == '|')
		return (2);
	else if (input[i] == '>' && input[i + 1] == '>')
		return (3);
	else if (input[i] == '<' && input[i + 1] == '<')
		return (4);
	else if (input[i] == '|')
		return (5);
	else if (input[i] == '>')
		return (6);
	else if (input[i] == '<')
		return (7);
	return (0);
}

char	*format_input(char *input)
{
	int		i;
	int		j;
	char	*temp;
	int		receiver;

	i = 0;
	i = skip_space(input, i);
	j = 0;
	temp = malloc(sizeof(char) * ft_strlen(input));
	while(input[i])
	{
		receiver = chr_separator(input, i);
		if (receiver == 1 || receiver == 2 || receiver == 3 || receiver == 4)
		{
			if ((i > 0) && jump_char(input[i - 1]) != 1)
			{
				temp = ft_strjoin(temp, " ");;
				j++;
			}
			temp[j] = input[i];
			temp[j + 1] = input[i + 1];
			j = j + 2;
			i = i + 2;
			if (jump_char(input[i]) != 1)
			{
				temp = ft_strjoin(temp, " ");
				j++;
			}
			if (jump_char(input[i]) == 1)
			{
				i = skip_space(input, i);
				temp = ft_strjoin(temp, " ");
				j++;
			}
		}
		temp[j] = input[i];
		i++;
		j++;
	}
	return (temp);
}
/*char	**tokenizer(char *input)
{
	
}*/

/*int	main()
{
	printf("%s", format_input(">> ls>> ls"));
}*/