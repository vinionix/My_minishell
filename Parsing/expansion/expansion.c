/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:07:31 by gada-sil          #+#    #+#             */
/*   Updated: 2025/06/12 16:39:41 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static bool	find_env_match(t_vars *var, char *old, int i, t_env *env_lst)
{
	while (env_lst)
	{
		if (old[i] == '\0')
		{
			free(old);
			return (true);
		}
		if (!ft_strcmp_limited(old + (i + 1), env_lst->key, '$'))
		{
			if (var->first_time)
			{
				var->temp_str = ft_substr(var->result, 0, i);
				var->first_time = false;
			}
			else
				var->temp_str = ft_substr(var->result, 0,
						ft_strlen(var->result));
			free(var->result);
			var->result = join_strings(var->temp_str, env_lst->value);
			break ;
		}
		env_lst = env_lst->next;
	}
	return (false);
}

static char	*expand(char *old, t_env *env_lst)
{
	size_t	i;
	t_vars	var;
	char	*not_found;

	var.result = ft_substr(old, 0, ft_strlen_until_char(old, '$'));
	i = strchr_index_next(var.result, '$', 0);
	var.temp_str = NULL;
	var.first_time = true;
	not_found = NULL;
	while (1337)
	{
		if (find_env_match(&var, old, i, env_lst))
			return (var.result);
		else
		{
			not_found = ft_substr(var.result, 0,
					ft_strlen_until_char(var.result, '$'));
			free(var.result);
			var.result = not_found;
			not_found = NULL;
		}
		if (i < ft_strlen(old))
			i = strchr_index_next(old, '$', i + 1);
	}
	return (NULL);
}

static void	set_dollar(char **matrix, bool *bools)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		if (have_char(matrix[i], '$'))
			bools[i] = true;
		i++;
	}
}

void	expand_variable(char **matrix, t_env *env_lst)
{
	bool	*bools;
	int		i;

	i = 0;
	bools = (bool *)malloc(sizeof(bool) * ft_len_matrix(matrix));
	if (!bools)
		return ;
	while (i < ft_len_matrix(matrix))
		bools[i++] = false;
	set_dollar(matrix, bools);
	i = 0;
	while (matrix[i])
	{
		if (bools[i] == true)
			matrix[i] = expand(matrix[i], env_lst);
		i++;
	}
	free(bools);
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
