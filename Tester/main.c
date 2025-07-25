/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:06:12 by vfidelis          #+#    #+#             */
/*   Updated: 2025/07/22 17:32:49 by gada-sil         ###   ########.fr       */
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

	t_env *envs = get_env_vars(env);

	char **unsetm = malloc(3 * 8);
	unsetm[0] = ft_strdup("unset");
	unsetm[1] = ft_strdup("HOME");
	unsetm[2] = NULL;
	create_default_env(&envs);
	ft_unset(unsetm, &envs);
	matrix = expand_and_wildcard(matrix, envs);

	return (exec_builtin(matrix, &envs, NULL));
	return (0);
}
