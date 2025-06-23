/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/06/12 16:14:36 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "../minishell.h"

typedef struct s_wildcard
{
	char			*file_dir;
	bool				match;
	unsigned int		index;
	struct s_wildcard	*next;
}				t_wildcard;

typedef struct s_var
{
	unsigned int	start;
	size_t			size;
	char			*current_card;
	unsigned int	ast;
}			t_var;

t_wildcard		*wild_lstnew(char *content);
void			wild_addback(t_wildcard **lst, t_wildcard *new);
int				strchr_index_next(const char *str, char stop,
					unsigned int start);
int				str_revcmp(const char *s1, const char *s2);
void			init_vars(t_var *vars);
int				read_current_dir(t_wildcard **list);
char			**list_to_matrix(t_wildcard *list);
void			free_wildlist(t_wildcard **list);
char			**join_matrices(char **matrix1, char **matrix2, int copy_until);


#endif
