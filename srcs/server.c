/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 13:58:49 by jaekpark          #+#    #+#             */
/*   Updated: 2021/06/23 21:15:43 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"
#include <stdio.h>

void init_flag(t_flag *flag)
{
	flag->len = 0;
	flag->len_bit = 0;
	flag->str = NULL;
	flag->str_bit = 0;
	flag->is_null = -1;
	flag->is_char = -1;
	flag->is_end = -1;
}

void make_buffer(t_flag *flag)
{
	if (flag->len > 0)
	{
		flag->len_bit++;
		flag->str = malloc(sizeof(char) * (flag->len + 1));
		flag->is_null = 0;
		flag->is_char = 1;
		ft_memset(flag->str, 0, flag->len + 1);
	}
	else if (flag->len == 0)
	{
		flag->len_bit++;
		flag->is_null = 1;
		flag->is_char = 1;
		ft_putstr_fd("\n", 1);
	}
}

void parse_len(int signum, t_flag *flag)
{
	if (signum == SIGUSR1)
		flag->len += 1 << (31 - flag->len_bit);
	flag->len_bit++;
	if (flag->len_bit == 32)
		make_buffer(flag);
}

void parse_str(int signum, t_flag *flag)
{
	static int i = 0;
	static int bit = 0;
	
	if (signum < 0 || !flag)
		return ;
	if (flag->is_null == 1)
	{
		ft_putchar_fd('\n', 1);
		flag->is_end = 1;
	}
	else
	{
		if (signum == SIGUSR1)
			flag->str[i] += 1 << (7 - bit);
		bit += 1;
		if (bit == 8)
		{
			i++;
			bit = 0;
			if (i == flag->len)
			{
				i = 0;
				ft_putstr_fd(flag->str, 1);
				flag->is_end = 1;
			}
		}
	}
}

void my_func(int signum, siginfo_t *siginfo, void *unused)
{
	static t_flag flag;
	static int is_first = 0;

	(void)siginfo;
	(void)unused;
	if (is_first == 0)
		init_flag(&flag);
	is_first = 1;
	if (flag.len_bit < 32)
		parse_len(signum, &flag);
	else if (flag.is_char == 1)
		parse_str(signum, &flag);
	if (flag.is_end == 1)
	{
		is_first = 0;
		init_flag(&flag);
		free(flag.str);
		return ;
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
