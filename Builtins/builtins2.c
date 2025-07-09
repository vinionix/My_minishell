/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 01:43:41 by gada-sil          #+#    #+#             */
/*   Updated: 2025/05/15 22:17:31 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	jump_space_and_0(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] == '0')
		i++;
	return (i);
}

static bool	only_numbers(char *str)
{
	int	i;

	i = jump_space_and_0(str);
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		i++;
	if (!ft_isdigit(str[i]))
		return (false);
	while (str[i])
	{
		if (!ft_isdigit((int)str[i]))
		{
			if (str[i] == ' ')
				return (str[jump_to_smt_else(str, ' ', i)] == '\0');
			else
				return (false);
		}
		i++;
	}
	return (true);
}

/*bool	long_check(char *str)
{
	
}*/

static unsigned char get_exit_code(char *str)
{
	unsigned char	exit_code;

	exit_code = (unsigned char)ft_atol(str, false);
	return (exit_code);
}

unsigned char	ft_exit(char **matrix, t_tree *tree, t_env *env)
{
	unsigned char	return_value;

	return_value = 0;
	if (!matrix)
		return (1);
	if (ft_len_matrix(matrix) == 1)
		ft_clean_and_exit(env, tree, return_value);
	else if (!only_numbers(matrix[1]))
	{
		printf("RETORNOU FALSE\n");
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", matrix[1]);
		ft_clean_and_exit(env, tree, 2);
	}
	else if (ft_len_matrix(matrix) > 2)
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		return_value = 1;
	}
	else
		ft_clean_and_exit(env, tree, get_exit_code(matrix[1]));
	return (return_value);
}
