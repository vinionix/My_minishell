/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:58:08 by gada-sil          #+#    #+#             */
/*   Updated: 2025/05/01 22:49:09 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int		strchr_index(const char *str, char stop)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != stop)
		i++;
	return (i);
}

static t_env   *create_nodes(const char **env)
{
    t_env	*lst;
    int		env_len;

	lst = NULL;
    env_len = 0;
    env_len = ft_len_matrix(env);
	while (env_len--)
		envadd_back(&lst, env_new());
	return (lst);
}

t_env    *get_env_vars(const char **env)
{
    t_env	*head;
	t_env	*temp;
    int		i;

    head = NULL;
	temp = NULL;
    i = 0;
    head = create_nodes(env);
	temp = head;
    while (*env)
    {
        i = strchr_index(*env, '=');
		temp->key = (char *)malloc(i + 1);
		temp->key[i] = '\0';
		while (--i >= 0)
			temp->key[i] = (*env)[i];
		i = strchr_index(*env, '=');
		i++;
		temp->value = ft_strdup(*env + i);
		temp = temp->next;
		env++;
    }
    return (head);
}

/*int main(int ac, char *av[], char *env[])
{
    t_env	*env_lst;

    (void)ac;
    (void)av;
    env_lst = NULL;

    env_lst = get_env_vars((const char **)env);
}*/