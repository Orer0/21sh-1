/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <aroblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 04:17:13 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/16 02:04:32 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

static void		set_init(t_term **t, int rel_cur, int tmp, char *cmd)
{
	int cur;

	cur = ((*t)->cur.x + ft_strlen((*t)->promtp)) % (*t)->col;
	tputs(tgetstr("cr", NULL), 0, &put);
	go_way(t, (*t)->len_p, ND);
	tputs(tgetstr("me", NULL), 0, &put);
	write(0, (*t)->line, ft_strlen((*t)->line));
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

static void		go_cut(t_term **t, int rel_cur, int tmp)
{
	cut(t, rel_cur, tmp);
	(*t)->max_cur = ft_strlen((*t)->line);
}

static void		manag_selec_direction(int *rel_cur, t_term **t
					, int *tmp, char *ky)
{
	tputs(tgetstr("vi", NULL), 0, &put);
	if (*rel_cur == 0)
		*tmp = mode_inver(t, *tmp);
	if (ky[0] == 27 && ky[1] == 91 && ky[2] == 68)
		*rel_cur = selec_left(t, *rel_cur);
	else if (ky[0] == 27 && ky[1] == 91 && ky[2] == 67)
		*rel_cur = selec_right(t, *rel_cur, *tmp);
}

static void		quit_selection_ctrl_c(t_term **t)
{
	t_shell_data	*data;

	data = shell_data_singleton();
	data->ctrl_c = FALSE;
	ft_strdel(&(*t)->line);
	ft_strdel(&(*t)->sel);
	put('\n');
	putst((*t)->promtp);
	reset_curse(t);
}

/*
**	SELEC - selec a part of line
**
**	params: t -> struct of the program term
**
**	Description:
**	- put the term il selec mode
**	- print the selec in reverse mode term
**	- if the cut, copy or selection mode by call the term leave the
**		selection mode and malloc a buffer of the selection
**	- initialize the old term params and the position of the curse
*/

void			selec(t_term **t)
{
	char			ky[1024];
	int				rel_cur;
	int				tmp;

	rel_cur = 0;
	tmp = (*t)->cur.x;
	ft_bzero(ky, 1024);
	while (!(ky[0] == -61 && ky[1] == -97) && !(ky[0] == -61 && ky[1] == -89))
	{
		ft_bzero(ky, 1024);
		read(0, ky, 6);
		manag_selec_direction(&rel_cur, t, &tmp, ky);
		if (ky[0] == -50 && ky[1] == -87)
		{
			go_cut(t, rel_cur, tmp);
			break ;
		}
		if (ky[0] == 3)
		{
			quit_selection_ctrl_c(t);
			break ;
		}
	}
	set_init(t, rel_cur, tmp, ky);
}
