/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <aroblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 05:34:03 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/02 01:11:30 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

void	print_promtp(t_term **t)
{
	ft_putstr((*t)->promtp);
	(*t)->index_his = -1;
	(*t)->cur.x = 0;
	(*t)->cur.y = 0;
	(*t)->max_cur = 0;
	(*t)->nb_line = 0;
	(*t)->rel_line = 0;
	(*t)->hist_line = 0;
}

void	go_down(t_term **t)
{
	if ((*t)->index_his <= -1)
	{
		while ((*t)->rel_line < (*t)->nb_line)
		{
			tputs(tgetstr("do", NULL), 0, &put);
			(*t)->rel_line++;
		}
	}
	else
	{
		while ((*t)->hist_line < (*t)->nb_line)
		{
			tputs(tgetstr("do", NULL), 0, &put);
			(*t)->rel_line++;
		}
	}
}

int		enter(t_term **t)
{
	t_list	*tmp;

	tmp = NULL;
	if ((*t)->line != NULL)
	{
		if (!(tmp = ft_lstnew((*t)->line, (ft_strlen((*t)->line) + 1))))
		{
			printf("creer erreur malloc\n");
			exit(-1);
		}
		ft_lstadd(&data->history, tmp);
		ft_strdel(&(*t)->line);
	}
	go_down(t);
	ft_putchar('\n');
	print_promtp(t);
	return (0);
}
