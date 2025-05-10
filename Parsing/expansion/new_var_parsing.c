/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_var_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:07:31 by gada-sil          #+#    #+#             */
/*   Updated: 2025/05/01 22:15:45 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "expansion.h"

static bool has_equals_sign(const char *str)
{
  while (*str)
  {
    if (*str == '=')
      return (true);
    str++;
  }
  return (false);
}

static void  create_env(const char *str, t_env *envs)
{
    int i;
    char *key;
    char *value;
    t_env *new;

    i = strchr_index(str, '=');
	  key = (char *)malloc(i + 1);
		key[i] = '\0';
		while (--i >= 0)
			key[i] = str[i];
	  i = strchr_index(str, '=');
		i++;
		value = ft_strdup(str + i);
    new = export_new_env(key, value);
    envadd_back(&envs, new);
}

int new_var_parsing(t_token *tokens, t_env *envs)
{
    int     i;
    int     j;
    int     error;

    i = 0;
    j = 0;
    error = 0;
    tokens = malloc(sizeof(t_token) * 7);
    for (int i = 0; i < 3; i++)
    {
	    tokens[i].value = "tchau*==adeus";
	    tokens[i].is_env = true;
    }
    tokens[6].value = NULL;
	  tokens[3].value = "=";
	  tokens[3].is_env = true;
	  tokens[4].is_env = true;
	  tokens[4].value = "=";
    tokens[5].value = "oi=10";
    tokens[5].is_env = true;
    while (tokens[i].value != NULL)
    {
    	if (tokens[i].is_env == true)
    	{
        if (!ft_isalpha((int)tokens[i].value[0]) && tokens[i].value[0] != '_')
        {
        	  printf("minishell: export: `%s': not a valid identifier\n", tokens[i++].value);
            j = 0;
        	  continue ;
        }
        while (tokens[i].value[j] && tokens[i].value[j] != '=')
        {
        	if (!ft_isalnum((int)tokens[i].value[j++]))
          {
				      printf("minishell: export: `%s': not a valid identifier\n", tokens[i++].value);
				      j = 0;
              error = 1;
				      break ;
          }
        }
        if (error)
        {
          error = 0;
          continue ;
        }
        if (has_equals_sign((const char *)tokens[i].value))
          create_env(tokens[i].value, envs);
      }
      i++;
    }
  free(tokens);
  return (0);
}

/*int main(int ac, char **av, char **env)
{
  (void)ac;
  (void)av;
  t_env *temp = get_env_vars((const char **)env);
  built_env(temp);
  t_env *tm = temp;
  while (tm)
  {
    tm = tm->next;
    free(temp->key);
    free(temp->value);
    free(temp);
    temp = tm;
  }
  char *oi = built_pwd();
  logs(oi);
  free(oi);
  built_cd("../");
  oi = built_pwd();
  logs(oi);
  free(oi);
  t_env *envs = get_env_vars((const char **)env);
  t_token *tokens;
  tokens = NULL;
  new_var_parsing(tokens, envs);
  for (int i = 0; envs; i++)
  {
    printf("%s %s\n", envs->key, envs->value);
    envs = envs->next;
  }
  envs = temp;
  while (temp)
  {
    temp = temp->next;
    free(envs->key);
    free(envs->value);
    free(envs);
    envs = temp;
  }
}*/
