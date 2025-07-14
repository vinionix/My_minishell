/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:19:27 by vfidelis          #+#    #+#             */
/*   Updated: 2025/07/12 16:23:28 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	final_pos_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i + 1].value != NULL)
		i++;
	return (i);
}

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

void	redir_add_back(t_redir **redirects, t_redir *node)
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

static t_redir *creat_list_redir(int id, t_token *tokens)
{
	t_redir	*redirects;
	int		i;

	i = 0;
	redirects = NULL;
	while ((tokens)[i].id != id)
		i++;
	while ((tokens)[i].id >= 0 && ((tokens)[i].type != TK_COMMAND 
		&& (!((tokens)[i].type >= TK_PIPE && (tokens)[i].type <= TK_OR))))
		i--;
	i++;
	while ((tokens)[i].value && ((tokens)[i].type != TK_COMMAND 
		&& (!((tokens)[i].type >= TK_PIPE && (tokens)[i].type <= TK_OR))))
	{
		if ((tokens)[i].type >= TK_FILE_IN && (tokens)[i].type <= TK_EOF)
			redir_add_back(&redirects, creator_node_redir((tokens)[i]));
		i++;
	}
	return (redirects);
}

t_tree	*node_creator(t_token *tokens, int id)
{
	int	i;
	t_tree	*node;

	i = 0;
	while ((tokens)[i].value && (tokens)[i].id != id)
		i++; 
	if ((tokens)[i].value == NULL)
		return (NULL);
	node = (t_tree *)ft_calloc(1, sizeof(t_tree));
	node->n_builtin = -1;
	node->type = (tokens)[i].type;
	node->id_tree = id;
	node->left = NULL;
	node->right = NULL;
	node->subtree = NULL;
	node->prev = NULL;
	node->main = 0;
	if ((tokens)[i].type == TK_COMMAND)
	{
		node->n_builtin = 0; //is_bultin(tokens);
		node->u_define.command.cmd = creat_command(id, tokens);
		node->u_define.command.list_redir = creat_list_redir(id, tokens);
	}
	else if ((tokens)[i].type == TK_PIPE)
		pipe(node->u_define.pipe.pipefd);
	return(node);
}

int	search_left(t_token **tokens, int id)
{
	int	i;
	int	flag;
	int	receiver;
	
	i = 0;
	flag = -1;
	receiver = 0;
	while ((*tokens)[i].value != NULL && (*tokens)[i].id != id)
		i++;
	i--;
	while (i >= 0 && (*tokens)[i].passed == -1)
	{
		if ((((*tokens)[i].type == TK_AND || (*tokens)[i].type == TK_OR) && flag != 1))
		{
			flag = 1;
			receiver = i;
		}
		else if ((*tokens)[i].type == TK_PIPE && flag != 1 && flag != 2)
		{
			flag = 2;
			receiver = i;
		}
		else if ((*tokens)[i].type == TK_COMMAND && flag != 1 && flag != 2 && flag != 3)
		{
			flag = 3;
			receiver = i;
		}
		i--;
	}
	if ((*tokens)[receiver].passed == 1)
		return (-1);
	(*tokens)[receiver].passed = 1;
	return ((*tokens)[receiver].id);
}

int	search_right(t_token **tokens, int id)
{
	int	i;
	int	flag;
	int	receiver;
	
	i = 0;
	flag = -1;
	receiver = 0;
	while ((*tokens)[i].value && (*tokens)[i].id != id)
		i++;
	if ((*tokens)[i + 1].value != NULL)
		i++;
	while ((*tokens)[i].value != NULL && (*tokens)[i].passed == -1)
	{
		if ((*tokens)[i].type == TK_PIPE && flag != 2)
		{
			flag = 2;
			receiver = i;
		}
		else if ((*tokens)[i].type == TK_COMMAND && flag != 2 && flag != 3)
		{
			flag = 3;
			receiver = i;
		}
		i++;
	}
	if ((*tokens)[receiver].passed == 1)
		return (-1);
	(*tokens)[receiver].passed = 1;
	return ((*tokens)[receiver].id);
}

t_tree	*search_for_bigger(t_token **tokens)
{
	int	i;
	int	flag;
	int	receiver;

	i = final_pos_tokens((*tokens));
	flag = 0;
	receiver = 0;
	while (i >= 0)
	{
		if ((((*tokens)[i].type == TK_AND || (*tokens)[i].type == TK_OR) && flag != 1))
		{
			flag = 1;
			receiver = i;
		}
		else if ((*tokens)[i].type == TK_PIPE && flag != 1 && flag != 2)
		{
			flag = 2;
			receiver = i;
		}
			else if ((*tokens)[i].type == TK_COMMAND && flag != 1 && flag != 2 && flag != 3)
		{
			flag = 3;
			receiver = i;
		}
		i--;
	}
	(*tokens)[receiver].passed = 1;
	return (node_creator((*tokens), (*tokens)[receiver].id));
}

void	tree_creator(t_token **tokens, t_tree **tree, int id)
{
	int		id_left_creat;
	int		id_right_creat;

	if (id == -1)
	{
		(*tree) = search_for_bigger(tokens);
		printf("main: %d\n", (*tree)->id_tree);
		(*tree)->main = 1;
		id = (*tree)->id_tree;
	}
	id_left_creat = search_left(tokens, id);
	id_right_creat = search_right(tokens, id);
	if (id_left_creat != -1)
	{
		(*tree)->left = node_creator((*tokens), id_left_creat);
		printf("left: %d\n", (*tree)->left->id_tree);
		(*tree)->left->prev = *tree;
		tree_creator(&(*tokens), &(*tree)->left, id_left_creat);
	}
	if (id_right_creat != -1)
	{
		(*tree)->right = node_creator((*tokens), id_right_creat);
		printf("rigth: %d\n", (*tree)->right->id_tree);
		(*tree)->right->prev = *tree;
		tree_creator(&(*tokens), &(*tree)->right, id_right_creat);
	}
}
