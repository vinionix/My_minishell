#include <stdio.h>

int fatorial(int fat)
{
    int red = fat;
    if (fat > 1)
    {
        fat--;
        printf("%d\n", red);
        red = red * fatorial(fat);
    }
    return (red);
}

int main()
{
    printf("%d", fatorial(5));
}
