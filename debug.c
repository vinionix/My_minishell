#include "minishell.h"

void logi(int nbr, ...)
{
    int i = -1;
    va_list	args;
    va_start(args, nbr);

    while(++i < nbr)
        printf("%d\n", va_arg(args, int));

    va_end(args);
}

void logs(int nbr, ...)
{
    int i = -1;
    va_list	args;
    va_start(args, nbr);

    while(++i < nbr)
        printf("%s\n", va_arg(args, char *));
    va_end(args);
}