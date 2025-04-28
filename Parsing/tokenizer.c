/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:39:07 by vfidelis          #+#    #+#             */
/*   Updated: 2025/04/28 04:27:20 by vfidelis         ###   ########.fr       */
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

t_token	*tokenizer(char **matrix)
{
	t_token	*tokens;
	int		i;

	i = 0;
	tokens = malloc(sizeof(t_token) * (ft_len_matrix(matrix) + 1));
	while(matrix[i])
	{
		tokens[i].value = matrix[i];
		i++;
	}
	tokens[i].value = NULL;
	return (tokens);
}

int	main(int argc, char **argv)
{
	(void)argc;
	char *str;
	char **matriz;
	t_token	*tokens;

	str = format_input(argv[1]);
	printf("%s\n", str);
	matriz = ft_split(str, ' ');
	free(str);
	tokens = tokenizer(matriz);
	ft_lexer(&tokens);
	for (int i = 0; tokens[i].value != NULL; i++)
		printf("Token Number %d: %d\n", i, tokens[i].type);
}