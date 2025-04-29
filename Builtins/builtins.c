#include "../minishell.h"

void    bi_cd(const char *str)
{
    if (chdir(str))
        exit(1);
}

void    bi_echo_n(const char *str)
{
    printf("%s", str);
}

void    bi_echo(const char *str)
{
    printf("%s\n", str);
}

void    bi_pwd(void)
{
    char *pwd;
    pwd = getenv("PWD");
    printf("%s\n", pwd);
}