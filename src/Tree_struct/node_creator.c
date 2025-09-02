#include "../consha.h"

static void	init_node(t_tree *node, int id, int type)
{
	node->id_tree = id;
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->subtree = NULL;
	node->prev = NULL;
	node->main = 0;
}

t_tree	*node_creator(t_token **tokens, int id, int i)
{
	t_tree	*node;

	while (((*tokens)[i].value || (*tokens)[i].type == TK_SUBSHELL)
		&& (*tokens)[i].id != id)
		i++;
	if ((*tokens)[i].value == NULL && (*tokens)[i].type != TK_SUBSHELL)
		return (NULL);
	node = (t_tree *)ft_calloc(1, sizeof(t_tree));
	init_node(node, id, (*tokens)[i].type);
	if ((*tokens)[i].type == TK_COMMAND || ((*tokens)[i].type >= TK_REDIR_IN
		&& (*tokens)[i].type <= TK_HEREDOC))
	{
		if ((*tokens)[i].type == TK_COMMAND)
			node->u_define.command.cmd = creat_command(id, (*tokens));
		node->u_define.command.list_redir = creat_list_redir(id, tokens);
		if (node->type == TK_COMMAND)
			creat_here_command(&node);
		else if (node->type != TK_COMMAND)
			here_verify(node->u_define.command.list_redir, 0);
	}
	else if ((*tokens)[i].type == TK_PIPE)
		node->u_define.pipe.std_in = -1;
	else if ((*tokens)[i].type == TK_SUBSHELL)
		tree_creator(&(*tokens)[i].subshell, &node->subtree, -1);
	return (node);
}
