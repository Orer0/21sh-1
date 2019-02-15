/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 04:20:32 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/15 23:54:36 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/get_line.h"

/*
**	PASTE - paste the line part copy
**
**	params: t -> struct of the program term
**
**	Description:
**	- copy the selection in a tmp char *
**	- print the copy in the line
**	- change the curse value
*/

void	paste(t_term **t)
{
	char			*tmp;
	t_shell_data	*data;

	data = shell_data_singleton();
	tmp = NULL;
	if ((*t)->sel)
	{
		if (data->t->selec != NULL)
			ft_strdel(&data->t->selec);
		data->t->selec = ft_strdup((*t)->sel);
	}
	if (data->t->selec == NULL)
		return ;
	else
	{
		if (!(tmp = ft_strdup(data->t->selec)))
			end_shell(t, NULL);
	}
	if ((*t)->line != NULL && (*t)->cur.x < (*t)->max_cur)
	{
		print_insertion(t, tmp);
		tputs(tgetstr("le", NULL), 0, &put);
		(*t)->cur.x--;
	}
	else
		print_buf_end(tmp, t);
}
