#include "../consha.h"

static void	assign_flag(int *receiver, int *flag, int value_flag, int i)
{
	*flag = value_flag;
	*receiver = i;
}

void	check_priority(t_token **tokens, int i, int *receiver, int *flag)
{
	if ((((*tokens)[i].type == TK_AND || (*tokens)[i].type == TK_OR)
			&& *flag != 1))
		assign_flag(receiver, flag, 1, i);
	else if ((*tokens)[i].type == TK_SUBSHELL && *flag != 1 && *flag != 2)
		assign_flag(receiver, flag, 2, i);
	else if ((*tokens)[i].type == TK_PIPE && *flag != 1 && *flag != 2
			&& *flag != 3)
		assign_flag(receiver, flag, 3, i);
	else if ((*tokens)[i].type == TK_COMMAND && *flag != 1 && *flag != 2
			&& *flag != 3 && *flag != 4)
		assign_flag(receiver, flag, 4, i);
	else if ((*tokens)[i].type >= TK_REDIR_IN && (*tokens)[i].type <= TK_HEREDOC
			&& *flag != 1 && *flag != 2 && *flag != 3 && *flag != 4
			&& *flag != 5)
		assign_flag(receiver, flag, 5, i);
}
