/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_signal_kill.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 04:22:48 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/14 03:09:42 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

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
		{
			// ft_strdel(&(*t)->promtp);
			data->t->index_his = -1;
			data->t->cur.x = 0;
			data->t->cur.y = 0;
			data->t->max_cur = 0;
			data->t->nb_line = 0;
			data->t->rel_line = 0;
			data->t->hist_line = 0;
			ft_strdel(&data->t->line);
			ft_fd_printf(0, "\n%s", PROMPT);
		}
	}
}
