/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/06/26 05:33:38 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "../minishell.h"

# define EXPANSION_MARKER '\x1D'
# define SINGLE_QUOTE_MARKER '\x1F'

typedef struct s_wildcard
{
	char				*file_dir;
	bool				match;
	bool				is_hidden;
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
char			**list_to_matrix(t_wildcard *list, bool show_hidden);
void			free_wildlist(t_wildcard **list);
char			**join_matrices(char **matrix1, char **matrix2, int copy_until);
char			*update_vars(t_wildcard *list, const char *wildcard, t_var *var);
void			reset_matches(t_wildcard *list);
void			remove_quotes(char **matrix);
void			parse_quotes(char **matrix, char c, char quote_type, char marker);
int				count_chars(char *str);
void			reset_modified_chars(char **matrix, char c);
char			**command_with_asterisk(char **matrix);
bool			is_hidden_file(char *str);

#endif
