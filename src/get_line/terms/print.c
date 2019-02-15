/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <aroblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 22:29:48 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/15 23:51:58 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

static void		buf_tab(char **buf)
{
	ft_strdel(buf);
	*buf = ft_strdup("        ");
}
/*
void		go_new_line(t_term **t)
{
	put(' ');
	tputs(tgetstr("cr", NULL), 0, put);
	(*t)->rel_line++;
	(*t)->nb_line++;
}
*/

/*
**	PRINT_BUF_END - print charactere in the end of line
**
**	params: t -> struct whit all cursors and final line
**			buf -> charactere top print
**
**	Description:
**	- check if is tabulation
**	- print the character
**	- if the cursor is at the end of terminal, insert a space and
**		increment rel_line and nb_line
**	- change the line in the struct
**	- change max_cur with the size of the line
**	- free buf
*/

void			print_buf_end(char *buf, t_term **t)
{
	int		len;

	if (buf[0] == 9)
		buf_tab(&buf);
	len = ft_strlen(buf);
	write(0, buf, ft_strlen(buf));
	while (len > 0)
	{
		if (((*t)->cur.x + ft_strlen((*t)->promtp)) % (*t)->col == 0)
		{
			(*t)->rel_line++;
			(*t)->nb_line++;
		}
		(*t)->cur.x++;
		len--;
	}
	if ((*t)->line == NULL)
		(*t)->line = ft_strdup(buf);
	else
		(*t)->line = ft_strjoin_free_s1(&(*t)->line, &buf);
	if (!(*t)->line)
		end_shell(t, NULL);
	(*t)->max_cur = ft_strlen((*t)->line);
	ft_strdel(&buf);
}

static void		calcl_len(t_term **t, char **buf)
{
	int		len;

	len = ft_strlen(*buf);
	while (len > 0)
	{
		(*t)->cur.x++;
		if (((*t)->cur.x + (*t)->len_p) % (*t)->col == 0)
			(*t)->rel_line++;
		len--;
	}
	if (ft_strlen(*buf) == 1)
		go_way(t, ((*t)->max_cur - (*t)->cur.x), LE);
	else
	{
		(*t)->cur.x++;
		go_way(t, ((*t)->max_cur - (*t)->cur.x), LE);
	}
	ft_strdel(buf);
}

/*
**	PRINT_INSERTION - print charactere in the line
**
**	params: t -> struct whit all cursors and final line
**			buf -> charactere top print
**
**	Description:
**	- check if is tabulation
**	- clean all the curent line
**	- create the new with the character
**	- change the line in the struct with new line
**	- print the line
**	- call calcl_len for move the cursor in the good position
*/

void			print_insertion(t_term **t, char *buf)
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
