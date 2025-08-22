/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 23:07:59 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/20 19:20:58 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	copy_children(t_token *tokens, t_token *new, int i, int size)
{
	int	pos;

	pos = 0;
	i++;
	while (size--)
	{
		new[pos].id = tokens[i].id;
		new[pos].type = tokens[i].type;
		new[pos].passed = tokens[i].passed;
		new[pos].value = ft_strdup(tokens[i].value);
		new[pos++].subshell = tokens[i++].subshell;
	}
}

int	get_subshell_size(t_token *tokens, int i)
{
	int	init;
	int final;
	int	size;

	init = 1;
	final = 0;
	size = 0;
	i++;
	while (final != init)
	{
		if (tokens[i].type == TK_INIT_PAREN)
			init++;
		else if (tokens[i].type == TK_FINAL_PAREN)
			final++;
		if (tokens[i].value)
			size++;
		i++;
	}
	return (size - 1);
}

void	skip_paren(t_token *tokens, int *i, int *final_size)
{
	int	init_paren;
	int	final_paren;
	
	if (final_size)
		(*final_size)++;
	final_paren = 0;
	init_paren = 1;
	(*i)++;
	while (final_paren != init_paren)
	{
		logs("oi");
		if (tokens[*i].type == TK_INIT_PAREN)
			init_paren++;
		else if (tokens[*i].type == TK_FINAL_PAREN)
			final_paren++;
		(*i)++;
	}
}

t_token	*remove_outter_paren(t_token *tokens, int i)
{
	t_token	*new;
	int		size;

	logs("SIZE:");
	size = get_subshell_size(tokens, i);
	new = (t_token *)malloc(sizeof(t_token) * (size + 1));
	new[size].value = NULL;
	copy_children(tokens, new, i, size);
	for (int i = 0; new[i].value; i++)
		printf("%s ", new[i].value);
	printf("%s", new[size].value);
	printf("\n");
	return (new);
}

int	count_tokens(t_token *tokens, int i)
{
	int n;

	n = 0;
	i++;
	while (tokens[i].type != TK_INIT_PAREN && tokens[i].type != TK_FINAL_PAREN)
	{
		n++;
		i++;
	}
	if (tokens[i].type == TK_INIT_PAREN)
		//i = ignore_paren(tokens, i);
	while (tokens[i++].type != TK_FINAL_PAREN)
		n++;
	return (n);
}

int count_levels(t_token *tokens, int i)
{
	int init;
	int final;

	init = 0;
	final = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == TK_INIT_PAREN)
			init++;
		else if (tokens[i].type == TK_FINAL_PAREN)
			final++;
		i++;
		if (init == final)
			break;
	}
	return (init);
}

t_token	*size_new_tokens(t_token *tokens, int i)
{
	int		final_size;
	t_token	*new_tokens;

	final_size = 0;
	while (tokens[i].value != NULL)
	{
		while (tokens[i].value != NULL && tokens[i].type != TK_INIT_PAREN)
		{
			final_size++;
			i++;
		}
		if (tokens[i].type == TK_INIT_PAREN)
			skip_paren(tokens, &i, &final_size);
	}
	new_tokens = (t_token *)malloc(sizeof(t_token) * (final_size + 1));
	new_tokens[final_size].value = NULL;
	logi(final_size);
	return (new_tokens);
}

void    creat_subshell(t_token **tokens)
{
    int		i;
	int		pos;
	t_token	*new_tokens;

    i = 0;
	pos = 0;
	new_tokens = size_new_tokens(*tokens, i);
    while ((*tokens)[i].value)
	{
		while ((*tokens)[i].value && (*tokens)[i].type != TK_INIT_PAREN)
		{
			new_tokens[pos].id = (*tokens)[i].id;
			new_tokens[pos].type = (*tokens)[i].type;
			new_tokens[pos].passed = (*tokens)[i].passed;
			new_tokens[pos].value = ft_strdup((*tokens)[i].value);
			new_tokens[pos++].subshell = (*tokens)[i++].subshell;
		}
		if ((*tokens)[i].value && (*tokens)[i].type == TK_INIT_PAREN)
		{
			new_tokens[pos].type = TK_SUBSHELL;
			new_tokens[pos].subshell = remove_outter_paren(*tokens, i);
			new_tokens[pos].value = NULL;
			logs((*tokens)[i].value);
			logi(i);
			skip_paren((*tokens), &i, 0); // trocar talvez
			logs((*tokens)[i].value);
		}
		pos++;
	}
	printf("AQUI>\n");
	logs(new_tokens[6].value);
	exit(EXIT_FAILURE);
}
