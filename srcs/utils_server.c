/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_server.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:50:28 by parkjaekw         #+#    #+#             */
/*   Updated: 2021/06/25 19:59:59 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	init_flag(t_flag *flag)
{
	flag->len = 0;
	flag->total_bit = 0;
	flag->len_bit = 0;
	flag->str = NULL;
	flag->idx = 0;
	flag->str_bit = 0;
}

void	start_minitalk(t_flag *flag, int *is_start)
{
	init_flag(flag);
	*is_start = 1;
}

void	parse_len(int signum, t_flag *flag)
{
	if (signum == SIGUSR1)
		flag->len += 1 << (31 - flag->len_bit);
	flag->len_bit++;
}

void	parse_str(int signum, t_flag *flag)
{
	if (flag->len != 0 && flag->str == NULL)
	{
		flag->str = malloc(sizeof(char) * flag->len + 1);
		ft_memset(flag->str, 0, flag->len);
	}
	if (signum == SIGUSR1)
	{
		flag->str[flag->idx] += 1 << (7 - flag->str_bit);
		flag->str_bit++;
	}
	else if (signum == SIGUSR2)
		flag->str_bit++;
	if (flag->str_bit == 8)
	{
		flag->idx++;
		flag->str_bit = 0;
	}
}

void	end_minitalk(t_flag *flag, int *is_start)
{
	if (flag->str)
	{
		ft_putstr_fd(flag->str, 1);
		ft_putchar_fd('\n', 1);
		init_flag(flag);
		*is_start = 0;
		free(flag->str);
	}
}
