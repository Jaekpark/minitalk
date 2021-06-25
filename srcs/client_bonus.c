/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:57:03 by jaekpark          #+#    #+#             */
/*   Updated: 2021/06/25 18:33:53 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

static void int_to_sig(int cnt, int bit, pid_t server)
{
	if (bit > 0)
		int_to_sig(cnt / 2, bit - 1, server);
	if ((cnt % 2) == 1)
	{
		if (kill(server, SIGUSR1) == -1)
			handle_error(SIGNAL_ERR1);
	}
	else if ((cnt % 2) == 0)
	{
		if (kill(server, SIGUSR2) == -1)
			handle_error(SIGNAL_ERR1);
	}
	usleep(100);
}

static void	char_to_sig(char c, int bit, pid_t server)
{
	if (bit > 0)
		char_to_sig(c / 2, bit - 1, server);
	if ((c % 2) == 1)
	{
		if (kill(server, SIGUSR1) == -1)
			handle_error(SIGNAL_ERR1);
	}
	else if ((c % 2) == 0)
	{
		if (kill(server, SIGUSR2) == -1)
			handle_error(SIGNAL_ERR1);
	}
	usleep(500);
}

static int	send_msg(char *msg, pid_t server)
{
	int	i;
	int cnt;

	i = -1;
	cnt = ft_strlen(msg);
	if (!msg || server < 0)
		return (-1);
	if (msg[0] == '\0')
	{
		print_client_msg(getpid(), cnt, 1);
		if ((kill(server, SIGUSR1)) == -1)
			handle_error(SIGNAL_ERR2);
	}
	else
	{
		print_client_msg(getpid(), cnt, 0);
		int_to_sig(cnt, 31, server);
		while (msg[++i] != '\0')
			char_to_sig(msg[i], 7, server);
	}
	return (0);
}

static void	signal_handler(int signum, siginfo_t *siginfo, void *unused)
{
	if (signum < 0 || !siginfo || !unused)
		handle_error(SIGNAL_ERR3);
	else if (signum == SIGUSR2)
	{
		ft_putnbr_fd(siginfo->si_pid, 1);
		ft_putstr_fd(" server say > recevied well.\n", 1);
	}
}

int		main(int argc, char **argv)
{
	struct sigaction	action;
	pid_t				server;

	if (argc != 3 || !argv)
		handle_error(CLIENT_ARG_ERR);
	if ((check_ascii(argv[2])) == -1)
		handle_error(ASCII_ERR);
	server = ft_atoi(argv[1]);
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = signal_handler;
	if ((sigaction(SIGUSR1, &action, 0)) == -1)
		handle_error(SIGACTION_ERR);
	if ((sigaction(SIGUSR2, &action, 0)) == -1)
		handle_error(SIGACTION_ERR);
	if ((send_msg(argv[2], server)) == -1)
		handle_error(MSG_ERR);
	return (0);
}