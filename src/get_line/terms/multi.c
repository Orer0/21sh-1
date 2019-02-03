/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 05:39:21 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/03 05:14:17 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

void	multi_up(t_term **t)
{
	int		cur;

	cur = 0;
	if ((*t)->rel_line > 0)
	{
		cur = (((*t)->cur.x + (*t)->len_p) % (*t)->col);
		tputs(tgetstr("up", NULL), 0, &put);
		(*t)->rel_line--;
		(*t)->cur.x = ((*t)->col * ((*t)->rel_line)) + cur - (*t)->len_p;
		if (cur < (*t)->len_p && (*t)->rel_line == 0)
			cur = (*t)->len_p;
		tputs(tgetstr("cr", NULL), 0, &put);
		while (cur > 0)
		{
			tputs(tgetstr("nd", NULL), 0, &put);
			cur--;
		}
	}
}

void	multi_down(t_term **t)
{
	int		cur;

	cur = 0;
	if ((*t)->rel_line < (*t)->nb_line)
	{
		(*t)->rel_line++;
		cur = (((*t)->cur.x + (*t)->len_p) % (*t)->col);
		tputs(tgetstr("do", NULL), 0, &put);
		(*t)->cur.x = ((*t)->col * ((*t)->rel_line)) + cur - (*t)->len_p;
		if ((*t)->rel_line == (*t)->nb_line && (*t)->cur.x > (*t)->max_cur)
		{
			cur = (((*t)->max_cur + (*t)->len_p) % (*t)->col);
			(*t)->cur.x = (*t)->max_cur;
		}
		tputs(tgetstr("cr", NULL), 0, &put);
		while (cur > 0)
		{
			tputs(tgetstr("nd", NULL), 0, &put);
			cur--;
		}
	}
}
