/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouv_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 22:20:36 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/16 02:17:07 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

/*
**	WORD_LEFT - mouve the cursor to the next word in the left
**
**	params: t -> struct whit all cursors and final line
**
**	Description:
**	- check if the curse is after the 0 position on x axe
**	- skip all space and mouv to the next word with ft_left fonction
*/

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

/*
**	WORD_RIGHT - mouve the cursor to the next word in the right
**
**	params: t -> struct whit all cursors and final line
**
**	Description:
**	- check if the curse is before the last printed charactere
**	- skip all space and mouv to the next word with ft_right fonction
*/

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
