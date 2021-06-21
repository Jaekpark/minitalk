#include "../includes/minitalk.h"

void my_func(int signum, siginfo_t *siginfo, void *unused)
{
	static int	c = 0;
	static int	bit = 0;

	if (signum < 0 || !siginfo || !unused)
		return ;
	if (signum == SIGUSR1)
		c += 1 << (7 - bit);
	bit += 1;
	if (bit == 8)
	{
		ft_putchar_fd(c, 1);
		bit = 0;
		c = 0;
		if (kill(siginfo->si_pid, SIGUSR2) == -1)
			handle_error("Error signal\n");
	}
}

int main(int argc, char **argv)
{
	struct sigaction action;
	pid_t pid;

	pid = getpid();
	if (argc != 1 || !argv)
		handle_error(SERV_ARG_ERR);
	ft_putstr_fd(SERV_RUN, 1);
	ft_putstr_fd("Server PID : ", 1);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = my_func;
	if ((sigaction(SIGUSR1, &action, 0)) == -1)
		handle_error("Error sigaction\n");
	if ((sigaction(SIGUSR2, &action, 0)) == -1)
		handle_error("Error sigaction\n");
	while (1)
		pause();
	return (0);
}
