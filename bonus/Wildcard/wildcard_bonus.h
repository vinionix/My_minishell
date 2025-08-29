/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/28 14:54:34 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_BONUS_H
# define WILDCARD_BONUS_H

# include "../minishell_bonus.h"

# define EXPANSION_MARKER '\x1D'
# define DOLLAR_MARKER '\x01'
# define POSSIBLE_ENV_MARKER '\x1E'
# define SINGLE_QUOTE_MARKER '\x1F'
# define DOUBLE_QUOTE_MARKER '\x1C'

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
char			*update_vars(const char *wildcard, t_var *var);
void			reset_matches(t_wildcard *list);
void			remove_quotes(char **matrix);
void			parse_quotes(char **matrix);
int				count_chars(char *str);
void			reset_modified_chars(char **matrix, char c);
bool			is_hidden_file(char *str);
bool			edge_case(t_wildcard *list, const char *wildcard);
int				count_char(const char *str, char c);
bool			check_sufix(t_wildcard *list, const char *wildcard);
char			*compress_wildcards(char *str);
int				len_except(const char *str, char exception);
bool			double_wildcard(const char *str);
void			reduce(const char *str, char *new);
void			not_found(char **matrix, char *old_temp, int i);
void			update(t_var *var, const char **temp, int *i,
					const char *wildcard);

#endif
