#include "../consha.h"

int	ft_unset(char **matrix, t_env **envs)
{
	int	i;

	i = 0;
	while (matrix[++i] != NULL)
		unset_env_if(envs, matrix[i]);
	return (0);
}
