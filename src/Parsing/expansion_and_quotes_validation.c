#include "../Wildcard/wildcard.h"

char	**expand_and_wildcard(char **matrix, t_env *env_lst)
{
	parse_quotes(matrix);
	expand_variables(matrix, env_lst);
	reset_modified_chars(matrix, '$');
	remove_quotes(matrix);
	remove_backslashs(matrix);
	matrix = wildcard(matrix);
	reset_modified_chars(matrix, '*');
	reset_modified_chars(matrix, '\'');
	reset_modified_chars(matrix, '\"');
	return (matrix);
}
