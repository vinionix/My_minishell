/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_and_quotes_validation.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:07:31 by gada-sil          #+#    #+#             */
/*   Updated: 2025/06/26 06:10:55 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Wildcard/wildcard.h"

char	**expand_and_wildcard(char **matrix, t_env *env_lst)
{
	parse_quotes(matrix);
	expand_variables(matrix, env_lst);
	reset_modified_chars(matrix, '$');
	remove_quotes(matrix);
	matrix = wildcard(matrix);
	reset_modified_chars(matrix, '*');
	reset_modified_chars(matrix, '\'');
	reset_modified_chars(matrix, '\"');
	return (matrix);
}
