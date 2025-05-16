/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:06:12 by vfidelis          #+#    #+#             */
/*   Updated: 2025/05/13 19:19:34 by vfidelis         ###   ########.fr       */
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

static void	aux_main(const char **env)
{
	t_arg_main	args;

	(void)env;
	t_env *lala; 
	
	lala = get_env_vars(env);
	while ("!exit")
	{
		initialize_args_main(&args);
		args.rdline = readline("minishell$ ");
		if (!args.rdline)
		{
			printf("exit\n");
			break;
		}
		if (args.rdline)
		{
			if (args.rdline[0] != '\0')
			{
				tokenizer(&args);
				new_var_parsing(args.tokens, &lala);
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
	aux_main(env);
}
