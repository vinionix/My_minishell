/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:58:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/07/16 22:45:59 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here(char *eof)
{
	//int		pipefd[2];
	char	*readl;
	
	readl = NULL;
	while (ft_strcmp((const char *)readl, (const char *)eof))
	{
		readl = readline("> ");
	}
}