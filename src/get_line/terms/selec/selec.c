/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 04:17:13 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/03 05:21:19 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/get_line.h"

static void		set_init(t_term **t, int rel_cur, int tmp, char *cmd)
{
	int cur;

	cur = ((*t)->cur.x + ft_strlen((*t)->promtp)) % (*t)->col;
	tputs(tgetstr("cr", NULL), 0, &put);
	go_way(t, (*t)->len_p, ND);
	tputs(tgetstr("me", NULL), 0, &put);
	ft_putstr((*t)->line);
	tputs(tgetstr("cr", NULL), 0, &put);
	if (rel_cur <= 0)
		go_way(t, cur, ND);
	else if (rel_cur > 0)
	{
		go_way(t, tmp + ft_strlen((*t)->promtp), ND);
		(*t)->cur.x = tmp;
	}
	tputs(tgetstr("ve", NULL), 0, &put);
	ft_bzero(cmd, 1024);
}

static int		mode_inver(t_term **t, int tmp_cur)
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

static void		go_cut(t_term **t, int rel_cur, int tmp)
{
	cut(t, rel_cur, tmp);
	(*t)->max_cur = ft_strlen((*t)->line);
}

void	selec(t_term **t)
{
	char	ky[1024];
	int		rel_cur;
	int		tmp;

	ft_bzero(ky, 1024);
	rel_cur = 0;
	tmp = (*t)->cur.x;
	while (!(ky[0] == -61 && ky[1] == -97) && !(ky[0] == -61 && ky[1] == -89))
	{
		ft_bzero(ky, 1024);
		read(0, ky, 6);
		tputs(tgetstr("vi", NULL), 0, &put);
		if (rel_cur == 0)
			tmp = mode_inver(t, tmp);
		if (ky[0] == 27 && ky[1] == 91 && ky[2] == 68)
			rel_cur = selec_left(t, rel_cur);
		else if (ky[0] == 27 && ky[1] == 91 && ky[2] == 67)
			rel_cur = selec_right(t, rel_cur, tmp);
		if (ky[0] == -50 && ky[1] == -87)
		{
			go_cut(t, rel_cur, tmp);
			break ;
		}
	}
	set_init(t, rel_cur, tmp, ky);
}
