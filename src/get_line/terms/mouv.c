/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <aroblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 02:15:19 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/13 00:08:07 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

/*
**	FT_RIGHT - mouve curse on the right direction
**
**	params: t -> struct whit all curses and final line
**
**	Description:
**	- check if the curse is before the last printed charactere
**	- incremente the axe x curse
**	- use Termcap for move the curse in a screen
**	- add a space if the cur exceed the max size of terminal and increment
**		the rel_line curse (axe y)
*/

void	ft_right(t_term **t)
{
	if ((*t)->cur.x < (*t)->max_cur)
	{
		(*t)->cur.x++;
		tputs(tgetstr("nd", NULL), 0, &put);
		if ((*t)->nb_line > 0)
		{
			if (((*t)->cur.x + ft_strlen((*t)->promtp)) % (*t)->col == 0)
			{
				put('\n');
				(*t)->rel_line++;
			}
		}
	}
}

/*
**	FT_LEFT - mouve curse on the left direction
**
**	params: t -> struct whit all cursors and final line
**
**	Description:
**	- check if the curse is after the 0 position on x axe
**	- decrement the rel_line curse (axe y) if the cursor go back to the
**		top line
**	- decrement the axe x cursor
**	- use Termcap for move the cursor in a screen
*/

void	ft_left(t_term **t)
{
	if ((*t)->cur.x > 0)
	{
		if (((*t)->cur.x + ft_strlen((*t)->promtp)) % (*t)->col == 0)
			(*t)->rel_line--;
		(*t)->cur.x--;
		tputs(tgetstr("le", NULL), 0, &put);
	}
}
