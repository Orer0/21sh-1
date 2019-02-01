/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 04:20:32 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/01 20:04:47 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

void	paste(t_term **t)
{
	char	*tmp;

	tmp = NULL;
	if ((*t)->sel == NULL)
		return ;
	else
		tmp = ft_strdup((*t)->sel);
	if ((*t)->line != NULL && (*t)->cur.x < (*t)->max_cur)
		print_insertion(t, tmp);
	else
		print_buf_end(tmp, t);
	tputs(tgetstr("le", NULL), 0, &put);
	(*t)->cur.x--;
}
