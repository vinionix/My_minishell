#include "../consha.h"

static void	initialize_args_main(t_arg_main *args)
{
	args->rdline = NULL;
	args->tree = NULL;
	args->matrix = NULL;
	args->temp = NULL;
	args->tokens = NULL;
}

static int	ft_is_space(char *rdline)
{
	int	i;

	i = 0;
	if (rdline == NULL)
		return (0);
	while (rdline[i] && rdline[i] <= 32)
		i++;
	if (rdline[i] == '\0')
		return (1);
	return (0);
}

static	char *get_prompt(char *prompt, char *cwd)
{
	char	*modified_cwd = ft_strjoin("\33[29m", cwd);
	modified_cwd = join(modified_cwd, "\33[0m");
	char	*med = ft_strjoin(prompt, modified_cwd);
	char	*res = ft_strjoin(med, "\n\33[1;33m❯\33[0m ");
	free(cwd);
	free(med);
	free(modified_cwd);
	return (res);
}

static void	aux_main(void)
{
	t_arg_main	args;
	char	*prompt = "\033[1;33m෧consha ⇀\033[0m";
	while (42)
	{
		set_signal();
		initialize_args_main(&args);
		char *prompt_with_dir = get_prompt(prompt, get_pwd());
		args.rdline = readline(prompt_with_dir);
		handle_sigint_code();
		if (ft_is_space(args.rdline))
		{
			free(args.rdline);
			args.rdline = NULL;
		}
		else if (!args.rdline)
		{
			printf("exit\n");
			if (get_data()->env)
				free_list(get_data()->env);
			break ;
		}
		if (args.rdline)
			exec_consha(&args);
		if (args.rdline)
			free(args.rdline);
		free(prompt_with_dir);
	}
}

int	main(int ac, char **av, const char **env)
{
	t_env	*envs;

	(void)ac;
	(void)av;
	envs = get_env_vars(env);
	get_data()->env = envs;
	create_default_env(&envs);
	init_data();
	printf("Welcome to \033[1;33mconsha\033[0m!\n");
	aux_main();
	return (0);
}
