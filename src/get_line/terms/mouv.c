/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <aroblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 02:15:19 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/02 00:16:51 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

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
				ft_putchar('\n');
				(*t)->rel_line++;
			}
		}
	}
}

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
