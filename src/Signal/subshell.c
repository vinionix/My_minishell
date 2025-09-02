/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 23:12:17 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/01 01:07:30 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../consha.h"

void	subshell_handler(int sig)
{
	(void)sig;
	g_signal_v++;
	rl_replace_line("", 0);
	rl_on_new_line();
}
