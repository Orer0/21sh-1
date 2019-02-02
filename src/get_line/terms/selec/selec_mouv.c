/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selec_mouv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 04:10:41 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/02 05:15:09 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

static void		left_rev(t_term **t, int rel_cur)
{
	char	*line;

	line = NULL;
	tputs(tgetstr("mr", NULL), 0, &put);
	write(STDOUT_FILENO, &((*t)->line[(*t)->cur.x]), 1);
	line = ft_strsub((*t)->line, (*t)->cur.x, (rel_cur * -1) + 1);
	(*t)->sel = ft_strdup(line);
	ft_strdel(&line);
	tputs(tgetstr("le", NULL), 0, &put);
	tputs(tgetstr("me", NULL), 0, &put);
}

static void		right_rev(t_term **t, int tmp_cur, int rel_cur)
{
	tputs(tgetstr("mr", NULL), 0, &put);
	write(STDOUT_FILENO, &((*t)->line[(*t)->cur.x]), 1);
	(*t)->sel = ft_strsub((*t)->line, tmp_cur, rel_cur + 1);
	tputs(tgetstr("me", NULL), 0, &put);
}

int				selec_left(t_term **t, int rel_cur)
{
	int		cur;

	cur = 0;
	if ((*t)->cur.x > 0)
	{
		ft_strdel(&(*t)->sel);
		tputs(tgetstr("le", NULL), 0, &put);
		(*t)->cur.x--;
		rel_cur--;
		cur = ((*t)->cur.x + ft_strlen((*t)->promtp)) % (*t)->col;
		tputs(tgetstr("cr", NULL), 0, &put);
		go_way(t, cur, ND);
		if (rel_cur < 0)
			left_rev(t, rel_cur);
		else if (rel_cur > 0)
		{
			tputs(tgetstr("me", NULL), 0, &put);
			write(STDOUT_FILENO, &((*t)->line[(*t)->cur.x]), 1);
			tputs(tgetstr("le", NULL), 0, &put);
		}
	}
	return (rel_cur);
}

int				selec_right(t_term **t, int rel_cur, int tmp_cur)
{
	int		cur;

	cur = ((*t)->cur.x + (*t)->len_p) % (*t)->col;
	if ((*t)->cur.x < (*t)->max_cur)
	{
		ft_strdel(&(*t)->sel);
		tputs(tgetstr("cr", NULL), 0, &put);
		go_way(t, cur, ND);
		if (((*t)->cur.x + ft_strlen((*t)->promtp)) % (*t)->col == 0)
		{
			ft_putchar('\n');
			(*t)->rel_line++;
		}
		if (rel_cur >= 0)
			right_rev(t, tmp_cur, rel_cur);
		else if (rel_cur < 0)
		{
			tputs(tgetstr("me", NULL), 0, &put);
			write(STDOUT_FILENO, &((*t)->line[(*t)->cur.x]), 1);
		}
		rel_cur++;
		(*t)->cur.x++;
	}
	return (rel_cur);
}
