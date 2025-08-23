/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:39:07 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/22 18:57:29 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	tokens[i].type = -1;
	return (tokens);
}

// DEBUG -- REMOVER PARA ENTREGAR ---- //
void print_subshells(t_token *tokens)
{
	if (!tokens || (tokens->value == NULL && tokens->type != TK_SUBSHELL))
		return ;
	if (tokens->type == TK_SUBSHELL && tokens->subshell)
		print_subshells(tokens->subshell);
	else if (tokens->value)
		printf("%s ", tokens->value);
	print_subshells(tokens + 1);
}
// ----------------------------------- //

int	tokenizer(t_arg_main *args)
{
	args->temp = format_input(args->rdline);
	if (args->temp == NULL)
		return (1);
	args->matrix = ft_split(args->temp, ' ');
	args->tokens = create_tokens(args->matrix);
	if (args->temp != NULL)
		free(args->temp);
	ft_lexer(&args->tokens);
	if (sintaxe_error(&args->tokens) == 1)
	{
		free_tokens(args->matrix, args->tokens);
		return (1);
	}
	//creat_subshell(&args->tokens);
	//print_subshells(args->tokens);
	//exit(1);
	tree_creator(&args->tokens, &args->tree, -1);
	return (0);
}
