/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/05/16 04:06:53 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_vars(t_var *vars)
{
	vars->start = 0;
	vars->size = 0;
	vars->current_card = NULL;
}

static void	is_match(t_wildcard *list, const char *wildcard, t_var *var)
{
	int	ast = 0;
	var->current_card = ft_substr(wildcard, var->start, var->size - var->start);
	list->fileOrDir = ft_strdup("minishellbosta");
	if (var->start == 0 && ft_strncmp(list->fileOrDir,
			(const char *)var->current_card, ft_strlen(var->current_card))
				&& wildcard[0] != '*')
	{
		list->match = false;
		logs("not a match");
		return ;
	}
	logs(var->current_card);
	free(var->current_card);
	var->current_card = NULL;
	logi(var->size);
	logi(var->start);
	while (42)
	{
		list->index += var->size - var->start;
		printf("index: %d\n", list->index);
		var->start = var->size + 1;
		var->size = strchr_index_next(wildcard, '*', var->start);
		if (var->size == 0)
			break ;
		var->current_card = ft_substr(wildcard, var->start, var->size - var->start);
		printf("card: %s\n", var->current_card);
		if (wildcard[var->start] == '\0')
		{
			logs("caiu");
			break ;
		}
		printf("\n%s\n", list->fileOrDir + list->index);
		if (!ft_strstr(list->fileOrDir + list->index, var->current_card))
		{
			printf("index: %d\n", list->index);
			printf("file: %s\n", list->fileOrDir);
			printf("char: %c\n", list->fileOrDir[list->index]);
			logs("not a match (strstr)");
		}
		printf("quantidade: %ld\n", list->index + (var->size - var->start));
		printf("\naq: %c\n", wildcard[list->index + (var->size - var->start) + 1 + ast]);
		if (wildcard[list->index + (var->size - var->start) + 1 + ast] == '\0')
		{
			printf("putz\n");
			if (str_revcmp(list->fileOrDir + list->index, var->current_card))
				printf("not a match (null)\n");
		}
		ast++;
		printf("char: %c\n", list->fileOrDir[list->index]);
		printf("start: %d\n", var->start);
	}
}

static int	parse_wildcard(t_wildcard *list,
				const char *wildcard, t_var *var)
{
	t_wildcard		*temp;
	int s = 0;

	var->size = strchr_index_next(wildcard, '*', var->start);
	while (42)
	{
		temp = list;
		//if (temp)
		{
			is_match(temp, wildcard, var);
		}
		free(var->current_card);
		var->current_card = NULL;
		break ;
		s++;
		if (s == 4)
			return 1;
	}
	return (0);
}

int	read_current_dir(t_wildcard **list)
{
	DIR			*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (dir == NULL)
	{
	perror("opendir");
	return (1);
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
	wild_addback(list,
		wild_lstnew((const char *)ft_strdup((const char *)entry->d_name)));
	entry = readdir(dir);
	}
	closedir(dir);
	return (0);
}
int main(int ac, char **av)
{
	(void)ac;
	t_wildcard	*list;
	t_var		var;
	const char *word;

	list = NULL;
	init_vars(&var);
	read_current_dir(&list);
	word = (const char *)ft_strdup(av[1]);
	parse_wildcard(list, word, &var);
	free((char *)word);
}
