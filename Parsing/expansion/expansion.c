/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:07:31 by gada-sil          #+#    #+#             */
/*   Updated: 2025/06/26 06:10:55 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

/*static bool	find_env_match(t_vars *var, char *old, int i, t_env *env_lst)
{
	return (false);
}*/
static char	**create_possible_envs(char *str, char *copy)
{
	
}

static char	*mark_expansions(char *str)
{
	int		i;
	char	*copy;

	i = strchr_index_next(str, '$', 0) + 1;
	copy = ft_strdup((const char *)str);
	while (copy[i])
	{
		while (copy[i] && copy[i] != ' ' && copy[i] != '$')
			copy[i++] = EXPANSION_MARKER;
		if (copy[i])
			i++;
		i = strchr_index_next(copy, '$', i) + 1;
	}
	return (copy);
}

static char	*expand(char *str, t_env *env_lst)
{
	char	**matrix;
	char	*copy;
	(void)env_lst;

	copy = mark_expansions(str);
	matrix = create_possible_envs(str, copy);
	
	
	return (NULL);
}

void	expand_variables(char **matrix, t_env *env_lst)
{
	int		i;

	i = 0;
	//parse_quotes(matrix, '\'', '\"', SINGLE_QUOTE_MARKER);
	//parse_quotes(matrix, '$', '\'', EXPANSION_MARKER);
	//remove_quotes(matrix);
	while (matrix[i])
	{
		if (have_char(matrix[i], '$'))
		{
			matrix[i] = expand(matrix[i], env_lst);
		}
		i++;
	}
	logs(matrix[0]);
	exit(1);
	reset_modified_chars(matrix, '$');
}
/*int	main(int ac, char **av, const char **env)
{
	(void)ac;
	(void)av;
	t_env *env1 = NULL;
	env1 = get_env_vars(env);
	char **matrix = malloc(sizeof(char *) * 2);
	matrix[0] = ft_strdup("AQUI: $$PWD$$$$$$$$US$PWD$");
	matrix[1] = NULL;
	expand_variable(matrix, env1);
	logs(matrix[0]);
	free(matrix[0]);
	free(matrix);
}*/
