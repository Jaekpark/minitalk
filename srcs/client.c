/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:57:03 by jaekpark          #+#    #+#             */
/*   Updated: 2021/06/25 20:03:12 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	str_to_sig(char *msg, int cnt, pid_t server)
{
	int	idx;
	int	bit;

	idx = 0;
	while (idx < cnt)
	{
		bit = 7;
		while (bit >= 0)
		{
			if ((msg[idx] >> bit) & 1)
				kill(server, SIGUSR1);
			else
				kill(server, SIGUSR2);
			bit--;
			usleep(100);
		}
		idx++;
	}
}

static void	len_to_sig(int cnt, pid_t server)
{
	int	bit;

	bit = 31;
	while (bit >= 0)
	{
		if ((cnt >> bit) & 1)
			kill(server, SIGUSR1);
		else
			kill(server, SIGUSR2);
		bit--;
		usleep(100);
	}
}

static int	send_msg(char *msg, pid_t server)
{
	int	i;
	int	cnt;

	i = -1;
	cnt = ft_strlen(msg);
	if (!msg || server < 0)
		return (-1);
	if (msg[0] == '\0')
	{
		if ((kill(server, SIGUSR1)) == -1)
			handle_error(SIGNAL_ERR2);
	}
	else
	{
		len_to_sig(cnt, server);
		str_to_sig(msg, cnt, server);
		usleep(100);
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

int			main(int argc, char **argv)
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
