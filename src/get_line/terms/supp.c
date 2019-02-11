/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <aroblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 02:22:48 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/03 05:09:35 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

void			new_line(t_term **t, int len, int size)
{
	char	*end;
	char	*line;

	end = NULL;
	if ((*t)->line != NULL)
		end = ft_strsub((*t)->line, len, ft_strlen((*t)->line + (*t)->cur.x));
	line = ft_strsub((*t)->line, 0, size);
	ft_strdel(&(*t)->line);
	if (line == NULL && end != NULL)
		(*t)->line = ft_strdup(end);
	else if (end == NULL && line != NULL)
		(*t)->line = ft_strdup(line);
	else
		(*t)->line = ft_strjoin(line, end);
	if ((*t)->line == NULL)
	{
		(*t)->max_cur = 0;
		(*t)->cur.x = 0;
		return ;
	}
	ft_strdel(&line);
	ft_strdel(&end);
}

static void		supp_in(t_term **t)
{
	int		len;

	len = (((*t)->cur.x + (int)ft_strlen((*t)->promtp)) / (*t)->col);
	delete_all(len, t);
	new_line(t, (*t)->cur.x, (*t)->cur.x - 1);
	(*t)->cur.x--;
	putst((*t)->line);
	(*t)->max_cur = ft_strlen((*t)->line);
	if (((*t)->cur.x + ft_strlen((*t)->promtp)) % (*t)->col == 0)
		(*t)->rel_line--;
	go_way(t, ((*t)->max_cur - (*t)->cur.x), LE);
}

static void		decal(t_term **t)
{
	putst((*t)->line);
	ft_putchar(' ');
	ft_putchar(' ');
	tputs(tgetstr("le", NULL), 0, &put);
	tputs(tgetstr("le", NULL), 0, &put);
}

static void		supp_end(t_term **t)
{
	int		len;
	char	*line;

	line = NULL;
	len = (((*t)->max_cur + (*t)->len_p) / (*t)->col);
	delete_all(len, t);
	if (!(line = ft_strsub((*t)->line, 0, (*t)->cur.x - 1)))
	{
		(*t)->max_cur = 0;
		(*t)->cur.x = 0;
		return ;
	}
	ft_strdel(&(*t)->line);
	if (!((*t)->line = ft_strdup(line)))
		end_shell(t, NULL);
	ft_strdel(&line);
	if (((*t)->cur.x - 1 + ft_strlen((*t)->promtp)) % (*t)->col == 0)
		decal(t);
	else
		putst((*t)->line);
	(*t)->max_cur = ft_strlen((*t)->line);
	(*t)->cur.x--;
	if (((*t)->cur.x + ft_strlen((*t)->promtp)) % (*t)->col == 0)
		(*t)->rel_line--;
	go_way(t, ((*t)->max_cur - (*t)->cur.x), LE);
}

int				supp(t_term **t)
{
	if ((*t)->cur.x > 0)
	{
		if ((*t)->cur.x < (*t)->max_cur)
			supp_in(t);
		else if ((*t)->cur.x == (*t)->max_cur)
			supp_end(t);
	}
	return (0);
}
