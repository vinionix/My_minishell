# 🐚 Minishell

Minishell é uma implementação em **C** de uma shell simplificada inspirada no Bash.  
Projeto desenvolvido como parte do currículo da 42 Rio, com foco em compreender como funcionam internamente os interpretadores de comandos no Unix/Linux.

---

## ✨ Funcionalidades
- Execução de comandos simples (ex: `ls`, `echo`, `pwd`).
- Suporte a múltiplos comandos encadeados com **pipes** (`|`).
- Redirecionamento de entrada e saída (`>`, `>>`, `<`).
- Tratamento de sinais (`CTRL+C`, `CTRL+D`, `CTRL+\`).
- Gerenciamento de variáveis de ambiente.
- Estrutura modular e expansível para novas funcionalidades.

---

## 🛠️ Tecnologias e Conceitos
- **Linguagem C**  
- **Processos**: `fork`, `execve`, `wait`, `waitpid`  
- **File descriptors** e manipulação de I/O  
- **Sinais**: `signal`, `sigaction`  
- **Parsing de comandos** e análise sintática  
- **Arquitetura Unix** e conceitos de sistemas operacionais  

---

## 🚀 Como executar
1. Clone o repositório:
   ```bash
   git clone https://github.com/seuuser/minishell.git
   cd minishell
Compile o projeto:

make

Execute a shell:
./minishell

📚 Aprendizados principais
Manipulação de processos e comunicação entre eles.

Implementação de pipes e redirecionamentos com file descriptors.

Tratamento de sinais e controle de execução.

Parsing da entrada do usuário e gerenciamento de memória.

Funcionamento interno de uma shell Unix.
