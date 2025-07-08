/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:06:12 by vfidelis          #+#    #+#             */
/*   Updated: 2025/07/08 18:08:26 by gada-sil         ###   ########.fr       */
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
	(void)env;

	char **matrix = malloc(3 * 8);
	matrix[0] = ft_strdup("exit");
	matrix[1] = ft_strdup("-1    ");
	matrix[2] = NULL;

	t_tree *null = NULL;
	t_env *envs = get_env_vars(env);


	printf("status code: %d\n", (int)ft_exit(matrix, null, envs));
	printf("Program did not finish!");

	free_matrix(matrix);
}
