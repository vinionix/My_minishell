/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:19:27 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/09 06:25:42 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*creator_node_redir(t_token tokens)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	redir->type = (tokens).type;
	redir->eof = NULL;
	redir->next = NULL;
	redir->file = NULL;
	if ((tokens).type == TK_EOF)
		redir->eof = ft_strdup((tokens).value);
	else if ((tokens).type >= TK_FILE_IN && (tokens).type <= TK_FILE_APP)
		redir->file = ft_strdup((tokens).value);
	return (redir);
}

static void	redir_add_back(t_redir **redirects, t_redir *node)
{
	t_redir	*head;

	if ((*redirects) == NULL)
	{
		(*redirects) = node;
		return ;
	}
	head = (*redirects);
	while ((*redirects)->next)
		(*redirects) = (*redirects)->next;
	(*redirects)->next = node;
	(*redirects) = head;
	return ;
}

t_redir *creat_list_redir(int id, t_token **tokens)
{
	t_redir	*redirects;
	int		i;

	i = 0;
	redirects = NULL;
	while ((*tokens)[i].id != id)
		i++;
	while ((*tokens)[i].id > 0 && (!((*tokens)[i].type >= TK_PIPE && (*tokens)[i].type <= TK_OR)))
		i--;
	i++;
	while ((*tokens)[i].value && (!((*tokens)[i].type >= TK_PIPE && (*tokens)[i].type <= TK_OR)))
	{
		if ((*tokens)[i].type >= TK_FILE_IN && (*tokens)[i].type <= TK_EOF)
		{
			(*tokens)[i - 1].passed = 1;
			redir_add_back(&redirects, creator_node_redir((*tokens)[i]));
		}
		i++;
	}
	return (redirects);
}

void	tree_creator(t_token **tokens, t_tree **tree, int id)
{
	int		id_left_creat;
	int		id_right_creat;

	if (id == -1)
	{
		(*tree) = search_for_bigger(tokens);
		(*tree)->main = 1;
		id = (*tree)->id_tree;
	}
	id_left_creat = search_left(tokens, id);
	id_right_creat = search_right(tokens, id);
	if (id_left_creat != -1)
	{
		(*tree)->left = node_creator(tokens, id_left_creat);
		(*tree)->left->prev = *tree;
		tree_creator(&(*tokens), &(*tree)->left, id_left_creat);
	}
	if (id_right_creat != -1)
	{
		(*tree)->right = node_creator(tokens, id_right_creat);
		(*tree)->right->prev = *tree;
		tree_creator(tokens, &(*tree)->right, id_right_creat);
	}
}
