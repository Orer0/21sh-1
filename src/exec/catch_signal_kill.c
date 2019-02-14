/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_signal_kill.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 04:22:48 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/14 23:24:41 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "get_line.h"

void		catch_signal_kill(int signal)
{
	t_shell_data	*data;

	data = shell_data_singleton();
	if (signal == SIGINT)
	{
		data->ctrl_c = TRUE;
		if (data->pid != 0)
		{
			kill(data->pid, SIGTERM);
			write(0, "\n", 1);
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
			tputs(tgetstr("ve", NULL), 0, &put);
			tputs(tgetstr("me", NULL), 0, &put);
			ft_strdel(&data->t->line);
			ft_fd_printf(0, "\n%s", PROMPT);
		}
	}
}
