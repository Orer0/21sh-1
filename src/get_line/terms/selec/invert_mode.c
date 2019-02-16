/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invert_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 02:03:52 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/16 02:05:18 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

int		mode_inver(t_term **t, int tmp_cur)
{
	ft_strdel(&(*t)->sel);
	tputs(tgetstr("mr", NULL), 0, &put);
	if (&((*t)->line[(*t)->cur.x]) != '\0')
		write(STDOUT_FILENO, &((*t)->line[(*t)->cur.x]), 1);
	tputs(tgetstr("le", NULL), 0, &put);
	(*t)->sel = ft_strsub((*t)->line, (*t)->cur.x, 1);
	tputs(tgetstr("me", NULL), 0, &put);
	tmp_cur = (*t)->cur.x;
	return (tmp_cur);
}
