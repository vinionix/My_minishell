#include "../../consha.h"

void	copy_token(t_token *new, t_token *tokens)
{
	new->id = tokens->id;
	new->type = tokens->type;
	new->passed = tokens->passed;
	new->value = ft_strdup(tokens->value);
	new->subshell = tokens->subshell;
}

void	copy_children(t_token *tokens, t_token *new, int i, int size)
{
	i++;
	while (size--)
		copy_token(new++, tokens + i++);
}

void	assign_subshell_token(t_token *new, t_token *tokens)
{
	new->id = tokens->id;
	new->type = TK_SUBSHELL;
	new->value = NULL;
	new->passed = tokens->passed;
}
