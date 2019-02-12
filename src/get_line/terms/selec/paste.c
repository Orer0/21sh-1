/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 04:20:32 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/12 21:22:27 by aroblin          ###   ########.fr       */
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
		if (data->selec != NULL)
			ft_strdel(&data->selec);
		data->selec = ft_strdup((*t)->sel);
	}
	if (data->selec == NULL)
		return ;
	else
	{
		if (!(tmp = ft_strdup(data->selec)))
			end_shell(t, NULL);
	}
	if ((*t)->line != NULL && (*t)->cur.x < (*t)->max_cur)
		print_insertion(t, tmp);
	else
		print_buf_end(tmp, t);
	tputs(tgetstr("le", NULL), 0, &put);
	(*t)->cur.x--;
}
