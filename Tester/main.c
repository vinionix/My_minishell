/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:06:12 by vfidelis          #+#    #+#             */
/*   Updated: 2025/07/14 20:20:56 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	initialize_args_main(t_arg_main *args)
{
	args->rdline = NULL;
	args->tree = NULL;
	args->matrix = NULL;
	args->temp = NULL;
	args->tokens = NULL;
}

static void	aux_main(void)
{
	t_arg_main	args;

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
				{
					free_tokens(args.matrix, args.tokens);
					exorcise_manager(&args.tree);
				}
			}
			add_history(args.rdline);
		}
		if (args.rdline)
			free(args.rdline);
	}
}

void free_env_list(t_env *list)
{
	t_env *temp;

	temp = list;
	while (temp)
	{
		temp = list->next;
		free(list->value);
		free(list->key);
		free(list);
		list = temp;	
	}
}

int	main(int ac, char **av, const char **env)
{
	(void)ac;
	(void)av;
	t_env *envs;

	envs = get_env_vars(env);
	get_data()->env = envs;
	aux_main();
}
