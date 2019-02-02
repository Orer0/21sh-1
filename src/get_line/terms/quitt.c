/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quitt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <aroblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 04:36:00 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/02 01:11:33 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_line.h"

// void	del_con(void *content, size_t size)
// {
// 	(void)size;
// 	ft_memdel(&content);
// }

void	quitt(t_term **t)
{
	(void)t; // a ssup
	if ((*t)->line != NULL)
		return ;
	ft_strdel(&(*t)->promtp);
	if ((*t)->sel != NULL)
		ft_strdel(&(*t)->sel);
	ft_memdel((void **)t);
}
