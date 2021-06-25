/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 21:32:41 by jaekpark          #+#    #+#             */
/*   Updated: 2021/06/25 18:33:48 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

int		check_ascii(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] > 127 || str[i] < 0)
			return (-1);
		i++;
	}
	return (1);
}

void	handle_error(char *err_msg)
{
	ft_putstr_fd(err_msg, 2);
	exit(1);
}
