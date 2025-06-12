/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:39:07 by vfidelis          #+#    #+#             */
/*   Updated: 2025/06/12 01:17:47 by vfidelis         ###   ########.fr       */
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
	temp = malloc(sizeof(char) * (ft_strlen(input) * 4 + 1));
	while (input[i])
	{
		chr_jump = jump_char(input[i]);
		if (chr_jump == 2 || chr_jump == 3)
		{
			temp[j++] = input[i++];
			while (input[i] && chr_jump != jump_char(input[i]))
				temp[j++] = input[i++];
			if (input[i] == '\0')
			{
				printf("Error\n");
				free(temp);
				return (NULL);
			}
		}
		receiver = chr_separator(input, i);
		if (receiver >= 1 && receiver <= 4)
		{
			if ((i > 0) && jump_char(input[i - 1]) != 1 && chr_separator(input,
					i - 1) == 0)
				temp[j++] = ' ';
			if (input[i + 1])
			{
				temp[j++] = input[i++];
				temp[j++] = input[i++];
			}
			if (input[i] && jump_char(input[i]) != 1)
				temp[j++] = ' ';
		}
		else if (receiver >= 5 && receiver <= 9)
		{
			if ((i > 0) && jump_char(input[i - 1]) != 1 && chr_separator(input,
					i - 1) == 0)
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
	if (matrix == NULL)
		return (NULL);
	tokens = malloc(sizeof(t_token) * (ft_len_matrix(matrix) + 1));
	while (matrix[i])
	{
		tokens[i].value = matrix[i];
		tokens[i].id = i;
		tokens[i].passed = -1;
		i++;
	}
	tokens[i].value = NULL;
	return (tokens);
}
#include <stdio.h>

char	*get_token_type_str(int type)
{
	if (type == TK_COMMAND) return ("COMMAND");
	if (type == TK_PIPE) return ("PIPE");
	if (type == TK_AND) return ("AND");
	if (type == TK_OR) return ("OR");
	if (type == TK_REDIR_IN) return ("REDIR_IN");
	if (type == TK_REDIR_OUT) return ("REDIR_OUT");
	if (type == TK_APPEND) return ("APPEND");
	if (type == TK_HEREDOC) return ("HEREDOC");
	return ("UNKNOWN");
}

void	print_tree(t_tree *node, int level)
{
	if (!node)
		return;
	for (int i = 0; i < level; i++)
		printf("    ");
	printf("[ID: %d] %s", node->id_tree, get_token_type_str(node->type));
	if (node->type == TK_COMMAND && node->u_define.command.cmd)
		printf(" CMD: \"%s\"", node->u_define.command.cmd[0]); // ou mais argumentos se quiser
	if (node->type == TK_HEREDOC)
		printf(" EOF: \"%s\"", node->u_define.here.eof);
	printf("\n");
	if (node->left || node->right)
	{
		print_tree(node->left, level + 2);
		print_tree(node->right, level + 1);
	}
}

int	tokenizer(t_arg_main *args)
{
	int	i;

	i = -1;
	args->temp = format_input(args->rdline);
	if (args->temp == NULL)
		return (1);
	printf("%s\n", args->temp);
	args->matrix = ft_split(args->temp, ' ');
	args->tokens = create_tokens(args->matrix);
	if (args->temp != NULL)
		free(args->temp);
	ft_lexer(&args->tokens);
	if (sintaxe_error(&args->tokens) == 1)
		return (1);
	while (args->tokens[++i].value != NULL)
	{
		if ((args->tokens[i + 1].value == NULL && args->tokens[i].type >= TK_PIPE
			&& args->tokens[i].type <= TK_OR))
		{
			printf("Error\n");
			free_tokens(args->matrix, args->tokens);
			return (1);
		}
	}
	t_tree	*tree;

	tree = NULL;
	tree_creator(&args->tokens, &tree, -1);
	print_tree(tree, 0);
	exit(0);
	if (args)
	{
		for (int i = 0; args->tokens[i].value != NULL; i++)
		printf("Command: %s <--------> Token Number %d: %d\n",
			args->tokens[i].value, args->tokens[i].id, args->tokens[i].type);
	}
	return (0);
}


