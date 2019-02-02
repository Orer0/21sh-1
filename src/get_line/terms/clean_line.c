/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <aroblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 04:36:00 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/02 04:58:27 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

void	clean_line(t_term **t)
{
	(void)t; // a ssup
	if ((*t)->line != NULL)
		return ;
	ft_strdel(&(*t)->promtp);
	if ((*t)->sel != NULL)
		ft_strdel(&(*t)->sel);
	ft_memdel((void **)t);
}
