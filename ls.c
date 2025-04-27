#include <unistd.h>

int main() {
    char *argv[] = {"ls", "-l", "Tester/", "src/", NULL};
    char *envp[] = {NULL};  // ou variáveis de ambiente reais

    execve("/bin/ls", argv, envp);
    return 0;
}
