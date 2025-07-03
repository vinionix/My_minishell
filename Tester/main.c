/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:06:12 by vfidelis          #+#    #+#             */
/*   Updated: 2025/06/26 06:00:17 by gada-sil         ###   ########.fr       */
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

	char **matrix = malloc(11 * 8);
	matrix[0] = ft_strdup("ls");
	matrix[1] = ft_strdup("$USER tem arquivos: ");
	matrix[2] = ft_strdup("'Arquivo *.txt está no diretório $HOME'");
	matrix[3] = ft_strdup("\"Arquivo atual é '$PWD/file.txt'\"");
	matrix[4] = ft_strdup("*\".txt\"$USER a $PWD");
	matrix[5] = ft_strdup("$USER\"\"");
	matrix[6] = ft_strdup("\"*\".txt\"\"");
	matrix[7] = ft_strdup("\"Usuario: $USER\"");
	matrix[8] = ft_strdup("'Path:'");
	matrix[9] = ft_strdup("$PATH");
	matrix[10] = NULL;

	t_env *env_lst = get_env_vars(env);
	matrix = expand_and_wildcard(matrix, env_lst);
	ft_echo(matrix);
	free_matrix(matrix);
	free_env_list(env_lst);
}
