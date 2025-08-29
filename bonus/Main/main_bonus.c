/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:06:12 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/29 20:29:20 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static void	initialize_args_main(t_arg_main *args)
{
	args->rdline = NULL;
	args->tree = NULL;
	args->matrix = NULL;
	args->temp = NULL;
	args->tokens = NULL;
}

static void	tokenizer_and_exec(t_arg_main *args)
{
	if (tokenizer(args) == 0)
	{
		free_tokens(args->tokens);
		free_split(args->matrix);
		exorcise_manager(&args->tree, 0);
		args->tree = NULL;
	}
}

static int	ft_is_space(char *rdline)
{
	int i = 0;

	if (rdline == NULL)
		return (0);
	while (rdline[i] && rdline[i] <= 32)
		i++;
	if (rdline[i] == '\0')
		return (1);
	return (0);
}

static void	aux_main(void)
{
	t_arg_main	args;

	get_data()->exit_code = 0;
	while (42)
	{
		set_signal();
		initialize_args_main(&args);
		args.rdline = readline("minishell$ ");
		handle_sigint_code();
		if (ft_is_space(args.rdline))
		{
			free(args.rdline);
			args.rdline = NULL;
		}
		else if (!args.rdline)
		{
			printf("exit\n");
			if (get_data()->env)
				free_list(get_data()->env);
			break ;
		}
		if (args.rdline)
		{
			signal(SIGINT, handle_sigint_no_redisplay);
			if (args.rdline[0] != '\0')
				tokenizer_and_exec(&args);
			add_history(args.rdline);
		}
		if (args.rdline)
			free(args.rdline);
	}
}

int	main(int ac, char **av, const char **env)
{
	t_env	*envs;

	(void)ac;
	(void)av;
	envs = get_env_vars(env);
	get_data()->env = envs;
	create_default_env(&envs);
	get_data()->exited_in_fork = false;
	get_data()->is_subshell = 0;
	get_data()->l_or_r = 0;
	get_data()->tokens = NULL;
	aux_main();
	return (0);
}
