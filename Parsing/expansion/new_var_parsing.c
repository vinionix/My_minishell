/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_var_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:07:31 by gada-sil          #+#    #+#             */
/*   Updated: 2025/05/01 22:15:45 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "expansion.h"

int new_var_parsing(t_token *tokens)
{
    int     i;
    int     j;

    i = 0;
    j = 0;
    tokens = malloc(sizeof(t_token) * 4);
    for (int i = 0; i < 3; i++)
    {
	    tokens[i].value = "tch*au=adeus";
	    tokens[i].is_env = true;
    }
    	tokens[3].value = NULL;
    while (tokens[i].value != NULL)
    {
    	if (tokens[i].is_env == true)
    	{
        	if (!ft_isalpha((int)tokens[i].value[0]) && tokens[i].value[0] != '_')
        	{
        	    printf("minishell: export: `%s': not a valid identifier\n", tokens[i++].value);
        	    continue ;
        	}
        	while (tokens[i].value[j] && tokens[i].value[j] != '=')
        	{
       			if (!ft_isalnum((int)tokens[i].value[j++]))
            		{
				printf("minishell: export: `%s': not a valid identifier\n", tokens[i++].value);
				j = 0;
				break ;
            		}
        	}
        	if (tokens[i].value)
		{
			if (tokens[i].value[j] == '=')
			{
				char *str = ft_strdup(tokens[i].value + (j + 1));
				i++;
				logs(str);
			}
		}
    	}
    }
    return (0);
}

int main()
{
	t_token *tokens;
	tokens = NULL;
	new_var_parsing(tokens);
}
