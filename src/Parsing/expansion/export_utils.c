#include "expansion.h"

int	check_first_char(char *variable)
{
	if (!ft_isalpha((int)variable[0]) && variable[0] != '_')
	{
		ft_putstr_fd("consha: export: `", 2);
		ft_putstr_fd(variable, 2);
		ft_putendl_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

int	check_following_chars(char *variable, char c)
{
	if (!ft_isalnum((int)c) && c != '_')
	{
		ft_putstr_fd("consha: export: `", 2);
		ft_putstr_fd(variable, 2);
		ft_putendl_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

void	create_variable_if(char *variable, t_env **envs, int *flag, int *ret)
{
	if (*flag == 1)
	{
		*flag = 0;
		*ret = 1;
		return ;
	}
	if (has_equals_sign((const char *)variable))
	{
		if (!find_env((const char *)variable, *envs))
			create_env((const char *)variable, envs);
		else
			change_env((const char *)variable, *envs);
	}
}

bool	has_equals_sign(const char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (true);
		str++;
	}
	return (false);
}
