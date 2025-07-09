/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/07/06 14:01:49 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**creat_command(int id_command, t_token *tokens)
{
	int	count_words;
	int i;
	int	j;
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
	command[0] = (tokens)[j].value; //usar strdup;
	if (count_words > 1)
	{

		i = 1;
		j++;
		while ((tokens)[j].value && (((tokens)[j].type != TK_COMMAND) 
			&& (!((tokens)[j].type >= TK_PIPE && (tokens)[j].type <= TK_OR))))
		{
			if ((tokens)[j].type == TK_CMD_ARG)
			{
				command[i] = (tokens)[j].value; //usar strdup;
				i++;
			}
			j++;
		}
	}
	return (command);
}
