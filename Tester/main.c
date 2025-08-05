/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:06:12 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/05 00:49:42 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	initialize_args_main(t_arg_main *args)
{
	args->rdline = NULL;
	args->matrix = NULL;
	args->temp = NULL;
	args->tokens = NULL;
}

void	aux_main(const char **env)
{
	t_arg_main	args;

	(void)env;
	while ("!exit")
	{
		initialize_args_main(&args);
		args.rdline = readline("minishell$ ");
		if (!args.rdline)
		{
			printf("exit\n");
			break ;
		}
		if (args.rdline)
		{
			if (args.rdline[0] != '\0')
			{
				if (tokenizer(&args) == 0)
					free_tokens(args.matrix, args.tokens);
			}
			add_history(args.rdline);
		}
		if (args.rdline)
			free(args.rdline);
	}
}

int	main(int ac, char **av, const char **env)
{
	(void)ac;
	//aux_main(env);
	char **matrix = malloc(ac * 8);
	for (int i = 0; i < ac - 1; i++)
		matrix[i] = ft_strdup(av[i + 1]);
	matrix[ac - 1] = NULL;

	for (int i = 0; matrix[i]; i++)
	{
		logs(matrix[i]);
	}
	t_env *envs = get_env_vars(env);

	create_default_env(&envs);
	matrix = expand_and_wildcard(matrix, envs);
	exec_builtin(matrix, &envs, NULL);
	for (int i = 0; i < ft_len_matrix(matrix); i++)
		free(matrix[i]);
	free(matrix);
	t_env *temp = envs;
	while (temp)
	{
		temp = envs->next;
		free(envs->key);
		free(envs->value);
		free(envs);
		envs = temp;
	}
	return (0);
}
