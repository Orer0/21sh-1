/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouv_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 22:20:36 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/03 05:14:23 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

void	word_left(t_term **t)
{
	if ((*t)->cur.x > 0)
	{
		while (ft_is_space((*t)->line[(*t)->cur.x]))
		{
			if ((*t)->cur.x <= 0)
				break ;
			ft_left(t);
		}
		while (!ft_is_space((*t)->line[(*t)->cur.x]))
		{
			if ((*t)->cur.x <= 0)
				break ;
			ft_left(t);
		}
	}
}

void	word_right(t_term **t)
{
	if ((*t)->cur.x < (*t)->max_cur)
	{
		while (ft_is_space((*t)->line[(*t)->cur.x]))
		{
			if ((*t)->cur.x >= (*t)->max_cur)
				break ;
			ft_right(t);
		}
		while (!ft_is_space((*t)->line[(*t)->cur.x]))
		{
			if ((*t)->cur.x >= (*t)->max_cur)
				break ;
			ft_right(t);
		}
	}
}
