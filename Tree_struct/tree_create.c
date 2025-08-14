/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/07/11 15:09:39 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	fill_command_array(char **command, t_token *tokens, int j)
{
	int	i;

	i = 1;
	j++;
	while ((tokens)[j].value && (((tokens)[j].type != TK_COMMAND)
		&& (!((tokens)[j].type >= TK_PIPE && (tokens)[j].type <= TK_OR))))
	{
		if ((tokens)[j].type == TK_CMD_ARG)
		{
			command[i] = ft_strdup((tokens)[j].value);
			i++;
		}
		j++;
	}
}

char	**creat_command(int id_command, t_token *tokens)
{
	int		count_words;
	int		i;
	int		j;
	char	**command;

	count_words = 1;
	i = 0;
	while ((tokens)[i].id != id_command)
		i++;
	j = i;
	i++;
	while ((tokens)[i].value && (((tokens)[i].type != TK_COMMAND)
		&& (!((tokens)[i].type >= TK_PIPE && (tokens)[i].type <= TK_OR))))
	{
		if ((tokens)[i].type == TK_CMD_ARG)
			count_words++;
		i++;
	}
	command = malloc(sizeof(char *) * (count_words + 1));
	command[count_words] = NULL;
	command[0] = ft_strdup((tokens)[j].value);
	if (count_words > 1)
		fill_command_array(command, tokens, j);
	return (command);
}
