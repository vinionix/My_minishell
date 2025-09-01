/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:06:12 by vfidelis          #+#    #+#             */
/*   Updated: 2025/09/01 01:20:59 by gada-sil         ###   ########.fr       */
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

static int	ft_is_space(char *rdline)
{
	int	i;

	i = 0;
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

	while (42)
	{
		set_signal();
		initialize_args_main(&args);
		args.rdline = readline("miniconsha$ ");
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
			exec_consha(&args);
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
	init_data();
	aux_main();
	return (0);
}
