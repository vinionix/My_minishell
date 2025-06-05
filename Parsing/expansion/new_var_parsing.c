/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_var_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:01:44 by vfidelis          #+#    #+#             */
/*   Updated: 2025/05/15 22:01:44 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "expansion.h"

t_env	*find_env(const char *target_key, t_env *envs)
{
	size_t	equals_sign;

	equals_sign = (size_t)strchr_index(target_key, '=');
	while (envs)
	{
		if (!(ft_strncmp(target_key, (const char *)envs->key, equals_sign)))
		{
			return (envs);
		}
		envs = envs->next;
	}
	return (NULL);
}

static int	change_env(const char *target_key, t_env *envs)
{
	t_env	*env_to_change;
	int		equals_sign;

	equals_sign = strchr_index(target_key, '=') + 1;
	env_to_change = find_env(target_key, envs);
	free(env_to_change->value);
	env_to_change->value = ft_strdup(target_key + equals_sign);
	return (0);
}

bool	has_equals_sign(const char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (true);
		str++;
	}
	return (false);
}

static void	create_env(const char *str, t_env **envs)
{
	int		i;
	char	*key;
	char	*value;
	t_env	*new;

	value = NULL;
	new = NULL;
	i = strchr_index(str, '=');
	key = (char *)malloc(i + 1);
	if (!key)
		return ;
	key[i] = '\0';
	while (--i >= 0)
		key[i] = str[i];
	i = strchr_index(str, '=');
	i++;
	value = ft_strdup(str + i);
	new = export_new_env(key, value);
	envadd_back(envs, new);
}

// Fazer mais testes nessa função mas no geral
// ela já consegue criar uma env, mostrar os
// erros se necessário e ela também já trata o
// caso de dar export em uma variável existente,
// o que faz com que apenas troque o valor da variável
// (também funciona se for algo tipo "variavel=", ela só
// substitui por um '\0', ficando com o mesmo comportamento do bash)
//
// REFATORAR PARA A NORMA
// ------------------------------------------------------------------
int	new_var_parsing(t_token *tokens, t_env **envs)
{
	int		i;
	int		j;
	int		error;

	i = 1;
	j = 0;
	error = 0;
	printf("oioi\n");
	while (tokens[i].value && tokens[i].type == TK_CMD_ARG)
	{
		if (!ft_isalpha((int)tokens[i].value[0]) && tokens[i].value[0] != '_')
		{
			printf("minishell: export: `%s': not a valid identifier\n",
				tokens[i++].value);
			j = 0;
			continue ;
		}
		while (tokens[i].value[j] && tokens[i].value[j] != '=')
		{
			if (!ft_isalnum((int)tokens[i].value[j++]))
			{
				printf("minishell: export: `%s': not a valid identifier\n",
					tokens[i++].value);
				j = 0;
				error = 1;
				break ;
			}
		}
		if (error)
		{
			error = 0;
			continue ;
		}
		if (has_equals_sign((const char *)tokens[i].value))
		{
			if (!find_env((const char *)tokens[i].value, *envs))
				create_env((const char *)tokens[i].value, envs);
			else
				change_env((const char *)tokens[i].value, *envs);
		}
		i++;
	}
	return (0);
}
