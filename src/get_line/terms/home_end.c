/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 02:18:03 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/01 04:43:26 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

void	cur_begin_line(t_term **t)
{
	size_t		i;

	i = (*t)->rel_line;
	if (i > 0)
	{
		while (i > 0)
		{
			tputs(tgetstr("up", NULL), 0, &put);
			i--;
		}
	}
	tputs(tgetstr("cr", NULL), 0, &put);
	go_way(t, (*t)->len_p, ND);
	(*t)->rel_line = 0;
	(*t)->cur.x = 0;
}

void	cur_end_line(t_term **t)
{
	int		k;
	int		i;

	i = (*t)->nb_line;
	k = ((*t)->max_cur + (*t)->len_p) % (*t)->col;
	if ((*t)->cur.x < (*t)->max_cur)
	{
		if (i > 0)
		{
			while (i > 0)
			{
				tputs(tgetstr("do", NULL), 0, &put);
				i--;
			}
		}
		tputs(tgetstr("cr", NULL), 0, &put);
		while (k > 0)
		{
			tputs(tgetstr("nd", NULL), 0, &put);
			k--;
		}
	}
	(*t)->rel_line = (*t)->nb_line;
	(*t)->cur.x = (*t)->max_cur;
}
