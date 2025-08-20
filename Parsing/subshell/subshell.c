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

int	ignore_paren(t_token *tokens, int i)
{
	int	init;
	int	final;

	init = 1;
	final = 0;
	i++;
	while (init != final)
	{
		if (tokens[i].type == TK_INIT_PAREN)
			init++;
		else if (tokens[i].type == TK_FINAL_PAREN)
			final++;
		i++;
	}
	return (i);
}

void	copy_outter(t_token *temp_tokens, t_token *tokens, int i)
{
	int pos;

	pos = 0;
	i++;
	while (tokens[i].type != TK_INIT_PAREN && tokens[i].type != TK_FINAL_PAREN)
	{
		temp_tokens[pos].type = tokens[i].type;
		temp_tokens[pos].id = tokens[i].id;
		temp_tokens[pos].passed = tokens[i].passed;
		temp_tokens[pos].list = tokens[i].list;
		temp_tokens[pos++].value = tokens[i++].value;
	}
	if (tokens[i].type == TK_INIT_PAREN)
		i = ignore_paren(tokens, i);
	while (tokens[i].value && tokens[i].type != TK_FINAL_PAREN)
	{
		temp_tokens[pos].type = tokens[i].type;
		temp_tokens[pos].id = tokens[i].id;
		temp_tokens[pos].passed = tokens[i].passed;
		temp_tokens[pos].list = tokens[i].list;
		temp_tokens[pos++].value = ft_strdup(tokens[i++].value);
	}
	for (int p = 0; temp_tokens[p].value; p++)
		logs(temp_tokens[p].value);
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
		i = ignore_paren(tokens, i);
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

void	create_subshell_list(t_token *tokens, t_token *subshell_tokens, // subshell_tokens[pos].tree
			int *i, int *pos)
{
	int	size_levels;
	t_token *temp_tokens;
	(void)pos;
	(void)subshell_tokens;

	size_levels = count_levels(tokens, *i);
	while (size_levels)
	{
		temp_tokens = (t_token *)malloc(sizeof(t_token) * (count_tokens(tokens, *i) + 1));
		temp_tokens[count_tokens(tokens, *i)].value = NULL;
		copy_outter(temp_tokens, tokens, *i);
		// agora vai
		
	}
	//subshell_tokens[*pos].list = subshell_new();
}

void	skip_paren(t_token *tokens, int *i, int *final_size)
{
	int	init_paren;
	int	final_paren;
	
	final_paren = 0;
	init_paren = 1;
	(*final_size)++;
	(*i)++;
	while (final_paren != init_paren)
	{
		if (tokens[*i].type == TK_INIT_PAREN)
		{
			init_paren++;
			(*final_size)++;
		}
		else if (tokens[*i].type == TK_FINAL_PAREN)
			final_paren++;
		(*i)++;
	}
}

t_token	*size_new_tokens(t_token *tokens)
{
	int	i;
	int	final_size;
	t_token	*new_tokens;

	i = 0;
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
	return (new_tokens);
}

void    creat_subshell(t_token **tokens)
{
    int i;
	int pos;
	t_token	*new_tokens;

    i = 0;
	pos = 0;
	new_tokens = size_new_tokens((*tokens));
    while ((*tokens)[i].value)
	{
		while ((*tokens)[i].value && (*tokens)[i].type != TK_INIT_PAREN)
		{
			new_tokens[pos].id = (*tokens)[i].id;
			new_tokens[pos].type = (*tokens)[i].type;
			new_tokens[pos].passed = (*tokens)[i].passed;
			new_tokens[pos].value = ft_strdup((*tokens)[i].value);
			new_tokens[pos++].list = (*tokens)[i++].list;
		}
		if ((*tokens)[i].value && (*tokens)[i].type == TK_INIT_PAREN)
		{
			new_tokens[pos].type = TK_SUBSHELL;
			create_subshell_list(*tokens, new_tokens, &i, &pos);
		}
	}
}