/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:06:12 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/12 19:08:06 by gada-sil         ###   ########.fr       */
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

void free_list(t_env *env)
{
	t_env *temp;

	temp = env;
	while (temp)
	{
		temp = env->next;
		if (env->value)
			free(env->value);
		if (env->key)
			free(env->key);
		if (env)
			free(env);
		env = temp;
	}
}

static void	aux_main(void)
{
	t_arg_main	args;

	get_data()->exit_code = 0;
	while (42)
	{
		initialize_args_main(&args);
		args.rdline = readline("minishell$ ");
		handle_sigint_code();
		if (!args.rdline)
		{
			printf("exit\n");
			if (get_data()->env)
				free_list(get_data()->env);
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
					args.tree = NULL;
				}
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
	t_env *envs;

	envs = get_env_vars(env);
	get_data()->env = envs;
	create_default_env(&envs);
	set_signal();
	get_data()->exited_in_fork = false;
	aux_main();
	return (0);
}
