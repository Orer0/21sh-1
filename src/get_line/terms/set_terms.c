/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_terms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <aroblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 02:26:41 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/12 22:58:01 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

void	set_terms(t_term **t, char *promtp)
{
	(*t)->cur.x = 0;
	(*t)->cur.y = 0;
	(*t)->index_his = -1;
	(*t)->line = NULL;
	(*t)->max_cur = 0;
	(*t)->col = 0;
	if (!((*t)->promtp = ft_strdup(promtp)))
		end_shell(t, NULL);
	(*t)->len_p = ft_strlen((*t)->promtp);
	(*t)->rel_line = 0;
	(*t)->nb_line = 0;
}
