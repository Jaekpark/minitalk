/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:57:03 by jaekpark          #+#    #+#             */
/*   Updated: 2021/06/23 20:57:19 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void int_to_sig(int cnt, int bit, pid_t server)
{
	if (bit > 0)
		int_to_sig(cnt / 2, bit - 1, server);
	if ((cnt % 2) == 1)
		if (kill(server, SIGUSR1) == -1)
			handle_error(SIGNAL_ERR);
	if ((cnt % 2) == 0)
		if (kill(server, SIGUSR2) == -1)
			handle_error(SIGNAL_ERR);
	usleep(100);
}

static void	char_to_sig(char c, int bit, pid_t server)
{
	if (bit > 0)
		char_to_sig(c / 2, bit - 1, server);
	if ((c % 2) == 1)
		if (kill(server, SIGUSR1) == -1)
			handle_error(SIGNAL_ERR);
	if ((c % 2) == 0)
		if (kill(server, SIGUSR2) == -1)
			handle_error(SIGNAL_ERR);
	usleep(100);
}

static int	send_msg(char *msg, pid_t server)
{
	int	i;
	int cnt;

	i = -1;
	cnt = ft_strlen(msg);
	if (!msg || server < 0)
		return (-1);
	int_to_sig(cnt, 31, server);
	while (msg[++i] != '\0')
		char_to_sig(msg[i], 7, server);
	return (0);
}

static void	signal_handler(int signum, siginfo_t *siginfo, void *unused)
{
	static int bit;

	bit = 0;
	if (signum < 0 || !siginfo || !unused)
		handle_error(SIGNAL_ERR);
	bit += 1;
	if (bit == 8)
	{
		ft_putstr_fd("1bit Signal received\n", 1);
		bit = 0;
	}
}

int		main(int argc, char **argv)
{
	struct sigaction	action;
	pid_t				server;

	if (argc != 3 || !argv)
		handle_error(CLIENT_ARG_ERR);
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