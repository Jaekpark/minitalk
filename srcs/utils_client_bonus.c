/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_client_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 17:50:37 by jaekpark          #+#    #+#             */
/*   Updated: 2021/06/25 19:59:45 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

void	print_client_msg(pid_t client, int cnt, int is_null)
{
	ft_putnbr_fd(client, 1);
	ft_putstr_fd(" client try to connect to server...\n", 1);
	ft_putstr_fd("...attemping to send ", 1);
	if (is_null == 0)
		ft_putnbr_fd(cnt, 1);
	else if (is_null == 1)
		ft_putstr_fd("only null", 1);
	ft_putstr_fd(" characters.\n", 1);
	usleep(100);
}
