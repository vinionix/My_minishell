/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 01:43:41 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/01 01:26:07 by gada-sil         ###   ########.fr       */
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

static bool	long_check(char *str)
{
	unsigned long long	max;
	unsigned long long	res;
	int					sign;
	int					i;

	i = jump_to_smt_else(str, '0', 0);
	if ((int)ft_strlen(str + i) > 19)
		return (false);
	max = LLONG_MAX;
	res = ft_atol(str, &sign);
	if (sign == 1)
	{
		if (res <= max)
			return (true);
		return (false);
	}
	if (res > max + 1)
		return (false);
	return (true);
}

static unsigned char	get_exit_code(char *str)
{
	unsigned char	exit_code;
	int				sign;

	exit_code = ft_atol(str, &sign);
	exit_code = (unsigned char)exit_code * sign;
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
	else if (!only_numbers(matrix[1]) || !long_check(matrix[1]))
	{
		write(2, "exit\n", 5);
		write(2, "miniconsha: exit: ", 19);
		write(2, matrix[1], ft_strlen(matrix[1]));
		write(2, ": numeric argument required\n", 28);
		ft_clean_and_exit(env, tree, 2);
	}
	else if (ft_len_matrix(matrix) > 2)
	{
		write(2, "exit\n", 5);
		print_error("miniconsha: exit: too many arguments", NULL);
		return_value = 1;
	}
	else
		ft_clean_and_exit(env, tree, get_exit_code(matrix[1]));
	return (return_value);
}
