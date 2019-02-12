/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_signal_kill.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 04:22:48 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/12 01:02:33 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		catch_signal_kill(int signal)
{
	t_shell_data	*data;

	data = shell_data_singleton();
	if (signal == SIGINT)
	{
		if (data->pid != 0)
		{
			kill(data->pid, SIGTERM);
			write(1, "\n", 1);
		}
		else
			ft_fd_printf(0, "\n%s", PROMPT);
	}
}
