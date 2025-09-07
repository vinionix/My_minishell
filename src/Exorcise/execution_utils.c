#include "../consha.h"

char	**attach_ls_flags(char **command)
{
	int	pos = 1;
	int		len = ft_len_matrix(command) + 2;
	char	**new_command = (char **)malloc((len + 1) * sizeof(char *));
	new_command[0] = ft_strdup(command[0]);
	new_command[1] = ft_strdup("--color=auto");
	new_command[2] = ft_strdup("-F");
	for (int i = 3; i < len; i++)
		new_command[i] = ft_strdup(command[pos++]);
	new_command[len] = NULL;
	free_matrix(command);
	return (new_command);
}

bool	is_command_directory(char *command)
{
	DIR				*dir;

	dir = opendir(command);
	if (dir == NULL)
		return (false);
	closedir(dir);
	return (true);
}

void	free_tree_and_env(void)
{
	free_tree(get_data()->head);
	free_list(get_data()->env);
}

t_tree	*last_left(t_tree *tree)
{
	while (tree->left && tree->left->type != TK_COMMAND
		&& tree->left->type != TK_SUBSHELL
		&& !(tree->left->type >= TK_REDIR_IN && tree->left->type <= TK_HEREDOC))
		tree = tree->left;
	return (tree);
}

char	**env_execv(t_env *env)
{
	char	*full_join;
	char	**env_exe;
	t_env	*temp;
	int		i;

	i = 0;
	temp = env;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	env_exe = (char **)ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (env)
	{
		full_join = ft_strjoin(env->key, "=");
		env_exe[i] = ft_strjoin(full_join, env->value);
		i++;
		free(full_join);
		env = env->next;
	}
	return (env_exe);
}

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}
