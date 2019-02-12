/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <aroblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 05:24:30 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/12 01:09:25 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

void	del(t_term **t)
{
	int			len;
	int			j;

	j = 0;
	len = 0;
	if ((*t)->cur.x < (*t)->max_cur)
	{
		len = (((*t)->cur.x + (int)ft_strlen((*t)->promtp)) / (*t)->col);
		delete_all(len, t);
		new_line(t, (*t)->cur.x + 1, (*t)->cur.x);
		if ((*t)->line == NULL)
			return ;
		putst((*t)->line);
		j = (((*t)->cur.x + (int)ft_strlen((*t)->promtp)) % (*t)->col);
		(*t)->max_cur--;
		if (j == 0 && (*t)->cur.x == (*t)->max_cur)
		{
			put(' ');
			tputs(tgetstr("le", NULL), 0, &put);
		}
		go_way(t, ((*t)->max_cur - (*t)->cur.x), LE);
	}
}
