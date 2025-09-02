#include "../consha.h"

void	subshell_handler(int sig)
{
	(void)sig;
	g_signal_v++;
	rl_replace_line("", 0);
	rl_on_new_line();
}
