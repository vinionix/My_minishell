#include "../minishell.h"

void logi(int x)         { printf("int: %d\n", x); }
void logfl(float x)     { printf("float: %.2f\n", x); }
void logd(double x)   { printf("double: %.2lf\n", x); }
void logc(char x)       { printf("char: '%c'\n", x); }
void logs(const char *x) { printf("string: \"%s\"\n", x); }