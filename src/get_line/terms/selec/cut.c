/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 04:19:05 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/01 22:01:52 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

void	cut(t_term **t, int rel_cur, int tmp)
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
	if (line == NULL && end != NULL)
		(*t)->line = ft_strdup(end);
	else if (end == NULL && line != NULL)
		(*t)->line = ft_strdup(line);
	else
		(*t)->line = ft_strjoin(line, end);
	ft_strdel(&line);
	ft_strdel(&end);
	delete_all(0, t);
}
