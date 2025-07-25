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
	(void)av;
	//aux_main(env);
	char **matrix = malloc(3 * 8);
	matrix[0] = ft_strdup("echo");
	matrix[1] = ft_strdup("$USER$a");
	matrix[2] = NULL;

	t_env *envs = get_env_vars(env);

	char **oi = malloc(3 * 8);
	oi[0] = ft_strdup("echo");
	oi[1] = ft_strdup("\"'a=expans$ao'\"");
	oi[2] = NULL;
	create_default_env(&envs);
	matrix = expand_and_wildcard(oi, envs);

	ft_echo(oi);

}
