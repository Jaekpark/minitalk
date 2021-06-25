/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 13:58:49 by jaekpark          #+#    #+#             */
/*   Updated: 2021/06/25 20:07:12 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

static void	print_pid(pid_t server)
{
	ft_putstr_fd(SERV_RUN, 1);
	ft_putstr_fd("Server PID : ", 1);
	ft_putnbr_fd(server, 1);
	write(1, "\n", 1);
}

static void	handle_null(pid_t client)
{
	if ((kill(client, SIGUSR2)) == -1)
		handle_error(SIGNAL_ERR1);
	ft_putnbr_fd(client, 1);
	ft_putstr_fd(" client say > ", 1);
	ft_putstr_fd("(null)\n", 1);
}

static void	signal_handler(int signum, siginfo_t *siginfo, void *unused)
{
	static t_flag	flag;
	static int		is_start = 0;

	if (!siginfo || !unused)
		return ;
	if (is_start == 0 && signum == SIGUSR1)
	{
		handle_null(siginfo->si_pid);
		return ;
	}
	if (is_start == 0)
		start_minitalk(&flag, &is_start);
	if (flag.total_bit < 32)
		parse_len(signum, &flag);
	if (flag.total_bit >= 32 && flag.total_bit < 32 + (flag.len * 8))
		parse_str(signum, &flag);
	flag.total_bit++;
	if (flag.total_bit == 32 + (flag.len * 8))
		end_minitalk(&flag, &is_start, siginfo);
}

int			main(int argc, char **argv)
{
	struct sigaction	action;
	pid_t				pid;

	pid = getpid();
	if (argc != 1 || !argv || pid < 0)
		handle_error(SERV_ARG_ERR);
	print_pid(pid);
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = signal_handler;
	if ((sigaction(SIGUSR1, &action, 0)) == -1)
		handle_error(SIGACTION_ERR);
	if ((sigaction(SIGUSR2, &action, 0)) == -1)
		handle_error(SIGACTION_ERR);
	while (1)
		pause();
	return (0);
}
