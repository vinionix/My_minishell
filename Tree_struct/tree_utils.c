/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:19:27 by vfidelis          #+#    #+#             */
/*   Updated: 2025/06/15 15:26:51 by vfidelis         ###   ########.fr       */
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



t_tree	*node_creator(t_token *tokens, int id)
{
	int	i;
	t_tree	*node;

	i = 0;
	while ((tokens)[i].value && (tokens)[i].id != id)
		i++; 
	if ((tokens)[i].value == NULL)
		return (NULL);
	node = malloc(sizeof(t_tree));
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
	}
	else if ((tokens)[i].type >= TK_REDIR_IN && (tokens)[i].type <= TK_APPEND)
	{
		if ((tokens)[i].type == TK_REDIR_IN)
			node->u_define.redir.fd = open((tokens)[i + 1].value, O_RDONLY);
		else if ((tokens)[i].type == TK_REDIR_OUT)
			node->u_define.redir.fd = open((tokens)[i + 1].value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if ((tokens)[i].type == TK_APPEND)
			node->u_define.redir.fd = open((tokens)[i + 1].value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else if ((tokens)[i].type == TK_HEREDOC)
		node->u_define.here.eof = ft_strdup((tokens)[i + 1].value);
	else if ((tokens)[i].type == TK_PIPE)
		pipe(node->u_define.pipe.pipefd);
	else if ((tokens)[i].type == TK_AND || (tokens)[i].type == TK_OR)
	{
		node->u_define.operators.result1 = -1;
		node->u_define.operators.result2 = -1;
	}
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
		else if ((*tokens)[i].type >= TK_REDIR_IN && (*tokens)[i].type <= TK_HEREDOC 
			&& flag != 1 && flag != 2 && flag != 3)
		{
			flag = 3;
			receiver = i;
		}
		else if ((*tokens)[i].type == TK_COMMAND && flag != 1 && flag != 2 && flag != 3 && flag != 4)
		{
			flag = 4;
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
		else if ((*tokens)[i].type >= TK_REDIR_IN && (*tokens)[i].type <= TK_HEREDOC 
			&& flag != 2 && flag != 3)
		{
			flag = 3;
			receiver = i;
		}
		else if ((*tokens)[i].type == TK_COMMAND && flag != 2 && flag != 3 && flag != 4)
		{
			flag = 4;
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
		else if ((*tokens)[i].type >= TK_REDIR_IN && (*tokens)[i].type <= TK_HEREDOC 
			&& flag != 1 && flag != 2 && flag != 3)
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
