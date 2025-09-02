/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 01:43:49 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/01 01:05:42 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../consha.h"

bool	is_command_directory(char *command)
{
	DIR				*dir;
	struct dirent	*entry;

	if ((command && command[0] && command[1]
			&& command[0] != '.' && command[1] != '/')
		|| !command[1])
		return (false);
	dir = opendir(".");
	if (dir == NULL)
	{
		perror("opendir");
		return (1);
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (ft_strcmp(entry->d_name, command + 2) == 0)
		{
			closedir(dir);
			return (true);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (false);
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
