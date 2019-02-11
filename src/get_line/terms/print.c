/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 22:29:48 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/09 21:43:29 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

static void	buf_tab(char **buf)
{
	ft_strdel(buf);
	*buf = ft_strdup("        ");
}

static void	go_new_line(t_term **t)
{
	ft_putchar(' ');
	tputs(tgetstr("cr", NULL), 0, put);
	(*t)->rel_line++;
	(*t)->nb_line++;
}

void	print_buf_end(char *buf, t_term **t)
{
	int		len;

	if (buf[0] == 9)
		buf_tab(&buf);
	len = ft_strlen(buf);
	ft_putstr(buf);
	while (len > 0)
	{
		(*t)->cur.x++;
		len--;
	}
	if (((*t)->cur.x + ft_strlen((*t)->promtp)) % (*t)->col == 0)
		go_new_line(t);
	if ((*t)->line == NULL)
		(*t)->line = ft_strdup(buf);
	else
		(*t)->line = ft_strjoin_free_s1(&(*t)->line, &buf);
	if (!(*t)->line)
		end_shell(t, NULL);
	(*t)->max_cur = ft_strlen((*t)->line);
	ft_strdel(&buf);
}

static void	calcl_len(t_term **t, char **buf)
{
	int		len;

	len = ft_strlen(*buf);
	while (len > 0)
	{
		(*t)->cur.x++;
		len--;
	}
	ft_strdel(buf);
	if (((*t)->cur.x + (*t)->len_p) % (*t)->col == 0)
		(*t)->rel_line++;
	go_way(t, ((*t)->max_cur - (*t)->cur.x), LE);
}

void	print_insertion(t_term **t, char *buf)
{
	char		*end;
	int			len;
	char		*line;

	if (buf[0] == 9)
		buf_tab(&buf);
	len = (((*t)->cur.x + (*t)->len_p) / (*t)->col);
	delete_all(len, t);
	if (!(end = ft_strsub((*t)->line, (*t)->cur.x,
		ft_strlen((*t)->line + (*t)->cur.x))))
		end_shell(t, NULL);
	line = ft_strsub((*t)->line, 0, (*t)->cur.x);
	if (!(end = ft_strjoin_free_s2(&buf, &end)))
		end_shell(t, NULL);
	ft_strdel(&(*t)->line);
	if (line == NULL)
		(*t)->line = ft_strdup(end);
	else
		(*t)->line = ft_strjoin(line, end);
	ft_strdel(&end);
	ft_strdel(&line);
	putst((*t)->line);
	(*t)->max_cur = ft_strlen((*t)->line);
	calcl_len(t, &buf);
}
