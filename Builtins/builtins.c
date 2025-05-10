/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 01:43:41 by gada-sil          #+#    #+#             */
/*   Updated: 2025/05/02 01:43:42 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    built_cd(const char *str)
{
  if (chdir(str))
    return (1);
  return (0);
}

int    built_echo_n(const char *str)
{
  printf("%s", str);
  return (0);
}

int    built_echo(const char *str)
{
  printf("%s\n", str);
  return (0);
}

char  *built_pwd(void)
{
  char    *pwd;
  size_t  size;

  pwd = NULL;
  size = 128;
  while (42)
  {
    pwd = (char *)malloc(size);
    if (!pwd)
    {
      perror("malloc");
      return (NULL);
    }
    if (getcwd(pwd, size) != NULL)
      return pwd;
    free(pwd);
    if (errno != ERANGE)
    {
      perror("getcwd");
      return (NULL);
    }
    size *= 2; 
  }
}

int built_env(t_env *env)
{
  t_env *temp;
  
  temp = env;
  if (!env)
    return (1);
  while (temp)
  {
    printf("%s", temp->key);
    printf("=");
    printf("%s\n", temp->value);
    temp = temp->next;
  }
  return (0);
}
