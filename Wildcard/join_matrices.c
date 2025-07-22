/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_matrices.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/07/22 17:55:01 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

char **join_matrices(char **matrix1, char **matrix2, int copy_until)
{
	int		new_size;
	char	**new_matrix;
	int		i;
	int		pos;

	new_size = ft_len_matrix(matrix1) + ft_len_matrix(matrix2);
	new_matrix = (char **)malloc(new_size * sizeof(char *));
	i = 0;
	pos = 0;
	while (matrix1[i] && i != copy_until)
		new_matrix[pos++] = ft_strdup(matrix1[i++]);
	i = 0;
	while (matrix2[i])
		new_matrix[pos++] = ft_strdup(matrix2[i++]);
	copy_until++;
	while (matrix1[copy_until])
		new_matrix[pos++] = ft_strdup(matrix1[copy_until++]);
	new_matrix[pos] = NULL;
	free_matrix(matrix1);
	free_matrix(matrix2);
	return (new_matrix);
}
