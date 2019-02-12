/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <aroblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 05:34:03 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/12 01:09:43 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

static void		reset_curse(t_term **t)
{
	(*t)->index_his = -1;
	(*t)->cur.x = 0;
	(*t)->cur.y = 0;
	(*t)->max_cur = 0;
	(*t)->nb_line = 0;
	(*t)->rel_line = 0;
	(*t)->hist_line = 0;
}

static void		go_down(t_term **t)
{
	if ((*t)->index_his <= -1)
	{
		while ((*t)->rel_line < (*t)->nb_line)
		{
			tputs(tgetstr("do", NULL), 0, &put);
			(*t)->rel_line++;
		}
	}
	else
	{
		while ((*t)->hist_line < (*t)->nb_line)
		{
			tputs(tgetstr("do", NULL), 0, &put);
			(*t)->rel_line++;
		}
	}
}

char			*enter(t_term **t)
{
	t_list			*tmp;
	t_shell_data	*data;

	data = shell_data_singleton();
	tmp = NULL;
	if ((*t)->line != NULL)
	{
		if (!(tmp = ft_lstnew((*t)->line, (ft_strlen((*t)->line) + 1))))
			end_shell(t, NULL);
		ft_lstadd(&data->history, tmp);
	}
	else
		(*t)->line = ft_strdup("\n");
	go_down(t);
	put('\n');
	reset_curse(t);
	return (NULL);
}
