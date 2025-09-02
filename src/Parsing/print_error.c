#include "../consha.h"

void	print_error(char *error_message, char *token)
{
	if (token)
	{
		ft_putstr_fd(error_message, 2);
		ft_putstr_fd(" ´", 2);
		ft_putstr_fd(token, 2);
		ft_putstr_fd("'", 2);
		ft_putstr_fd("\n", 2);
		return ;
	}
	ft_putstr_fd(error_message, 2);
	ft_putstr_fd("\n", 2);
}
