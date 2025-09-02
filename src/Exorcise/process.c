#include "../consha.h"

t_process	*node_process_creator(t_tree *node)
{
	t_process	*node_process;

	node_process = (t_process *)malloc(sizeof(t_process));
	node_process->prev = NULL;
	node_process->next = NULL;
	node_process->pid = -1;
	node_process->id_tree = node->id_tree;
	return (node_process);
}

void	process_add_back(t_process **main, t_process *node)
{
	t_process	*temp;

	temp = (*main);
	if ((*main) == NULL)
	{
		*main = node;
		return ;
	}
	while ((*main)->next != NULL)
		*main = (*main)->next;
	node->prev = *main;
	(*main)->next = node;
	*main = temp;
}
