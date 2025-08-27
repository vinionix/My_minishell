/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:13:00 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/27 16:06:05 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	logi(int x)
{
	printf("int: %d\n", x);
}

void	logfl(float x)
{
	printf("float: %.2f\n", x);
}

void	logd(double x)
{
	printf("double: %.2lf\n", x);
}

void	logc(char x)
{
	printf("char: '%c'\n", x);
}

void	logs(const char *x)
{
	printf("string: \"%s\"\n", x);
}
