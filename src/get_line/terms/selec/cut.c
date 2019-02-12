/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 04:19:05 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/12 20:33:42 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/get_line.h"

static void	cut_new_line(char *line, char *end, t_term **t)
{
	if (line == NULL && end != NULL)
		(*t)->line = ft_strdup(end);
	else if (end == NULL && line != NULL)
		(*t)->line = ft_strdup(line);
	else
		(*t)->line = ft_strjoin(line, end);
	if ((*t)->line == NULL)
		end_shell(t, NULL);
}

/*
**	CUT - cut a part of line
**
**	params: rel_cur -> the position of the curse
**			t -> struct of the program term
**			tmp -> old position of curse before selection
**
**	Description:
**	- create a new begin and end of line after that will be the new line
**		after the cut of the selection
**	- change the line in the new line in the struct
**	- free the tmp char *
**	- delete the line before the print of the new line
*/

void		cut(t_term **t, int rel_cur, int tmp)
{
	char	*end;
	char	*line;

	line = NULL;
	end = NULL;
	if (rel_cur <= 0)
	{
		end = ft_strsub((*t)->line, tmp + 1, ((*t)->max_cur - tmp));
		line = ft_strsub((*t)->line, 0, (*t)->cur.x);
	}
	else if (rel_cur > 0)
	{
		end = ft_strsub((*t)->line, (*t)->cur.x, (*t)->max_cur - (*t)->cur.x);
		line = ft_strsub((*t)->line, 0, tmp);
	}
	ft_strdel(&(*t)->line);
	cut_new_line(line, end, t);
	ft_strdel(&line);
	ft_strdel(&end);
	delete_all(0, t);
}
