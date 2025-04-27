/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:06:12 by vfidelis          #+#    #+#             */
/*   Updated: 2025/04/27 03:35:40 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	char *input;

	(void)ac;
	(void)av;
	(void)env;
	while ("!exit")
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if (*input)
			add_history(input);
		if (!ft_strncmp("pwd", input, 3))
			bi_pwd();
		else if (!ft_strncmp("cd", input, 2))
		{
			char *i = readline("colocar o lugar pra dar cd otario-> ");
			bi_cd(i);
		}
		//parsing(input);
		//printf("Você digitou: %s\n", input);
		free(input);
	}
}