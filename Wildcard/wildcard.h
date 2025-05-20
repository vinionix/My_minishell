/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/05/16 04:06:53 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

typedef struct s_wildcard
{
  const char		*fileOrDir;
  bool				match;
  unsigned int		index;
  struct s_wildcard	*next;
}					t_wildcard;

typedef struct s_var
{
	unsigned int	start;
	size_t			size;
	char *			current_card;
}					t_var;


t_wildcard	*wild_lstnew(const char *content);
void		wild_addback(t_wildcard **lst, t_wildcard *new);
int	strchr_index_next(const char *str, char stop, unsigned int start);
int	str_revcmp(const char *s1, const char *s2);

#endif
