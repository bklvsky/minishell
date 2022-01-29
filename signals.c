#include "includes/parser.h"

void	sig_int(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	here_sig(int signal)
{
	if (signal == SIGINT)
		exit(1);
}

void	child_sig(int signal)
{
	if (signal == SIGINT)
		write(1, "\n", 1);
}