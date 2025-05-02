/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:39:07 by vfidelis          #+#    #+#             */
/*   Updated: 2025/05/02 05:05:14 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*format_input(char *input)
{
	int		i;
	int		j;
	char	*temp;
	int		receiver;
	int		chr_jump;

	i = 0;
	chr_jump = 0;
	j = 0;
	temp = malloc(sizeof(char) * (ft_strlen(input) * 2));
	while(input[i])
	{
		chr_jump = jump_char(input[i]);
		if (chr_jump == 2 || chr_jump == 3)
		{
			temp[j++] = input[i++];
			while(input[i] && chr_jump != jump_char(input[i]))
				temp[j++] = input[i++];
			if (input[i] == '\0')
			{
				printf("Error");
				exit(1);
			}
		}
		receiver = chr_separator(input, i);
		if (receiver == 1 || receiver == 2 || receiver == 3 || receiver == 4)
		{
			if ((i > 0) && jump_char(input[i - 1]) != 1 && chr_separator(input, i - 1) == 0)
				temp[j++] = ' ';
			temp[j++] = input[i++];
			temp[j++] = input[i++];
			if (jump_char(input[i]) != 1)
				temp[j++] = ' ';
		}
		else if (receiver == 5 || receiver == 6 || receiver == 7)
		{
			if ((i > 0) && jump_char(input[i - 1]) != 1 && chr_separator(input, i - 1) == 0)
				temp[j++] = ' ';
			temp[j++] = input[i++];
			if (jump_char(input[i]) != 1)
				temp[j++] = ' ';
		}
		if (receiver == 0)
			temp[j++] = input[i++];
	}
	temp[j] = '\0';
	return (temp);
}

static t_token	*create_tokens(char **matrix)
{
	t_token	*tokens;
	int		i;

	i = 0;
	tokens = malloc(sizeof(t_token) * (ft_len_matrix(matrix) + 1));
	while(matrix[i])
	{
		tokens[i].value = matrix[i];
		tokens[i].id = i;
		i++;
	}
	tokens[i].value = NULL;
	return (tokens);
}

int	tokenizer(t_arg_main *args)
{
	int	i;

	i = -1;
	args->temp = format_input(args->rdline);
	printf("%s\n", args->temp);
	args->matrix = ft_split(args->temp, ' ');
	args->tokens = create_tokens(args->matrix);
	ft_lexer(&args->tokens);
	while (args->tokens[++i].value != NULL)
	{
		if (args->tokens[i + 1].value == NULL && args->tokens[i].type >= TK_PIPE && args->tokens[i].type <= TK_OR)
		{
			free_split(args->matrix);
			free(args->tokens);
			args->rdline2 = readline("> ");
			if (args->temp)
				args->return_join = ft_strjoin(args->temp, args->rdline2);
			else
				args->return_join = join(args->return_join, args->rdline2);
			args->temp2 = format_input(args->return_join);
			args->matrix = ft_split(args->temp2, ' ');
			args->tokens = create_tokens(args->matrix);
			ft_lexer(&args->tokens);
			sintaxe_error(&args->tokens);
			if (args->temp != NULL)
			{
				free(args->temp);
				args->temp = NULL;
			}
			args->rdline = args->return_join;
			i = -1;
		}
	}
	sintaxe_error(&args->tokens);
	for (int i = 0; args->tokens[i].value != NULL; i++)
		printf("Command: %s <--------> Token Number %d: %d\n", args->tokens[i].value, i, args->tokens[i].type);
	// free_split(matriz);
	// free(tokens);
	// free(oo);
	// free(argv[1]);
	// free(str);
	// free(temp);
	return (0);
}
