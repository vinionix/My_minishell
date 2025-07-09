/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:07:31 by gada-sil          #+#    #+#             */
/*   Updated: 2025/05/01 22:15:45 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "../../minishell.h"
# include "../../Wildcard/wildcard.h"

typedef struct envUtils
{
	int		i;
	int		final_len;
	char	*copy;
	char	*new_str;
}	t_vars;

t_env	*export_new_env(char *key, char *value);
bool	has_equals_sign(const char *str);
char	*join_strings(char *buffer, char *temp);
int		key_size(char *str);
int		ft_strlen_until_char(char *str, char c);
int		ft_strcmp_limited(char *s1, char *s2, char c);
int		check_first_char(char *variable);
int		check_following_chars(char *variable, char c);
void	create_variable_if(char *variable, t_env **envs, int *flag, int *ret);
int		change_env(const char *target_key, t_env *envs);
void	create_env(const char *str, t_env **envs);
void	expand_variables(char **matrix, t_env *env_lst);
void	reset_modified_chars(char **matrix, char c);

#endif
