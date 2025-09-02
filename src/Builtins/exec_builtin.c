#include "../consha.h"

static bool	is_only_char(char *str, char c, int i)
{
	if (!str)
		return (false);
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (str[i++] != c)
			return (false);
	}
	return (true);
}

bool	is_builtin(char *command)
{
	return (!ft_strcmp(command, "exit") || !ft_strcmp(command, "env")
		|| !ft_strcmp(command, "cd") || !ft_strcmp(command, "export")
		|| !ft_strcmp(command, "echo") || !ft_strcmp(command, "unset")
		|| !ft_strcmp(command, "pwd"));
}

static void	redirect_std(int std_in, int std_out)
{
	dup2(std_in, STDIN_FILENO);
	dup2(std_out, STDOUT_FILENO);
	close(std_in);
	close(std_out);
}

static void	aux_exec_builtin(char ***matrix,
	int *receiver, t_env **env)
{
	if (is_builtin((*matrix)[0]))
		(*matrix) = expand_and_wildcard((*matrix), *env);
	if (!ft_strcmp((*matrix)[0], "env"))
		*receiver = (ft_env(*env, (*matrix)));
	else if (!ft_strcmp((*matrix)[0], "cd"))
		*receiver = (ft_cd((*matrix), *env));
	else if (!ft_strcmp((*matrix)[0], "export") && !(*matrix)[1])
		*receiver = (export_no_args(*env));
	else if (!ft_strcmp((*matrix)[0], "export"))
		*receiver = (ft_export((*matrix), env));
	else if (!ft_strcmp((*matrix)[0], "echo") && (*matrix)[1]
		&& (*matrix)[1][0] == '-'
		&& is_only_char((*matrix)[1], 'n', 1))
		*receiver = (ft_echo_n((*matrix)));
	else if (!ft_strcmp((*matrix)[0], "echo"))
		*receiver = (ft_echo((*matrix)));
	else if (!ft_strcmp((*matrix)[0], "unset"))
		*receiver = (ft_unset((*matrix), env));
	else if (!ft_strcmp((*matrix)[0], "pwd"))
		*receiver = (ft_pwd((*matrix)));
}

int	exec_builtin(char ***matrix, t_env **envs, t_tree *tree)
{
	int	std_in;
	int	std_out;
	int	receiver;

	std_in = dup(STDIN_FILENO);
	std_out = dup(STDOUT_FILENO);
	receiver = 1337;
	if (if_redirect(tree->u_define.command.list_redir) == -1)
	{
		redirect_std(std_in, std_out);
		return (1);
	}
	aux_exec_builtin(matrix, &receiver, envs);
	if (!ft_strcmp((*matrix)[0], "exit"))
	{
		close(std_in);
		close(std_out);
		receiver = (ft_exit((*matrix), get_data()->head, *envs));
	}
	redirect_std(std_in, std_out);
	return (receiver);
}
