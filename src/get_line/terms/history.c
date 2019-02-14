/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <aroblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 02:02:30 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/14 01:34:41 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

static char		*ft_history(t_list **history, int index_his)
{
	t_list *tmp;

	tmp = *history;
	if (index_his < 0 || tmp == NULL)
		return (NULL);
	while (index_his > 0)
	{
		if (tmp->next != NULL)
			tmp = tmp->next;
		else
			return ((char *)tmp->content);
		index_his--;
	}
	return ((char *)tmp->content);
}

static void		set_new_value(t_term **t)
{
	char			*hist_l;
	t_shell_data	*data;

	data = shell_data_singleton();
	hist_l = NULL;
	if (!(hist_l = ft_strdup(ft_history(&data->t->history, (*t)->index_his))))
		end_shell(t, NULL);
	write(0, hist_l, ft_strlen(hist_l));
	if ((*t)->line != NULL)
		ft_strdel(&(*t)->line);
	if (!((*t)->line = ft_strdup(hist_l)))
		end_shell(t, NULL);
	(*t)->max_cur = ft_strlen(hist_l);
	(*t)->cur.x = (*t)->max_cur;
	(*t)->hist_line = ((*t)->max_cur / (*t)->col);
	ft_strdel(&hist_l);
}

/*
**	HISTORY_RIGHT - print the next hystory line
**
**	params: t -> struct whit all curses and final line
**
**	Description:
**	- change the maximum curse and the nomber of the line (axe y)
**	- delete all the charactere print in the screen after the prompt
**	- call set_new_value for print the corresponding hisory line
*/

int				history_up(t_term **t)
{
	t_shell_data	*data;

	data = shell_data_singleton();
	(*t)->max_cur = ft_strlen((*t)->line);
	(*t)->nb_line = (((*t)->max_cur + (*t)->len_p) / (*t)->col);
	if (data->t->history == NULL
		|| (*t)->index_his + 1 == ft_lstlen(data->t->history))
		return (1);
	else
		delete_all((*t)->nb_line, t);
	(*t)->index_his++;
	set_new_value(t);
	return (0);
}

/*
**	HISTORY_DOWN - print the previous hystory line
**
**	params: t -> struct whit all curses and final line
**
**	Description:
**	- change the maximum curse and the nomber of the line (axe y)
**	- delete all the charactere print in the screen after the prompt
**	- call set_new_value for print the corresponding hisory line
*/

int				history_down(t_term **t)
{
	t_shell_data	*data;

	data = shell_data_singleton();
	(*t)->max_cur = ft_strlen((*t)->line);
	(*t)->nb_line = (((*t)->max_cur + (*t)->len_p) / (*t)->col);
	if (data->t->history == NULL || (*t)->index_his < 0)
		return (1);
	else
		delete_all((*t)->nb_line, t);
	if ((*t)->index_his == 0 || ft_lstlen(data->t->history) <= 1)
	{
		cur_begin_line(t);
		tputs(tgetstr("cd", NULL), 0, &put);
		(*t)->index_his--;
		(*t)->max_cur = 0;
		ft_strdel(&(*t)->line);
		return (1);
	}
	if ((*t)->index_his == ft_lstlen(data->t->history))
		(*t)->index_his = (*t)->index_his - 2;
	else if ((*t)->index_his > 0)
		(*t)->index_his--;
	set_new_value(t);
	return (0);
}
