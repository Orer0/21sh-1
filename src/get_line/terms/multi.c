/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 05:39:21 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/12 22:33:13 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

/*
**	MULTI_UP - mouve the cursor to the line above
**
**	params: t -> struct whit all cursors and final line
**
**	Description:
**	- check if the curse is before the first line
**	- decrement the rel_line cursor
**	- move the cursor in the screen
**	- check if the cursor is under the prompt for a good positioning
*/

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

/*
**	MULTI_DOWN - mouve the cursor to the line below
**
**	params: t -> struct whit all cursors and final line
**
**	Description:
**	- check if the curse is before the last line
**	- increment the rel_line cursor
**	- move the cursor in the screen
**	- check if the last line is more short for a good positioning of cursor
*/

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
