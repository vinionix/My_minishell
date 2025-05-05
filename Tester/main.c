/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:06:12 by vfidelis          #+#    #+#             */
/*   Updated: 2025/05/02 04:18:15 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	initialize_args_main(t_arg_main *args)
{
	args->rdline = NULL;
	args->rdline2 = NULL;
	args->matrix = NULL;
	args->temp = NULL;
	args->temp2 = NULL;
	args->return_join = NULL;
	args->tokens = NULL;
}

static void	aux_main(char **env)
{
	t_arg_main	args;

	(void)env;
	initialize_args_main(&args);
	while ("!exit")
	{
		args.rdline = readline("minishell$ ");
		if (!args.rdline)
		{
			printf("exit\n");
			break;
		}
		tokenizer(&args);
		if (args.rdline)
			add_history(args.rdline);
		free(args.rdline);
	}
}

int	main(int ac, char **av, char **env)
{

	(void)ac;
	(void)av;
	aux_main(env);
}
