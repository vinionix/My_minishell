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

typedef struct	envUtils
{
	char	*result;
	char	*temp_str;
	bool	first_time;
}	t_vars;

bool	have_char(char *str, char c);
t_env	*export_new_env(char *key, char *value);
bool	has_equals_sign(const char *str);
t_env	*find_env(const char *target_key, t_env *envs);
char	*join_strings(char *buffer, char *temp);
int		key_size(char *str);
int		ft_strlen_until_char(char *str, char c);
int		ft_strcmp_limited(char *s1, char *s2, char c);

#endif
