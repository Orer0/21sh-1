/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_acceptor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 23:26:41 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/27 05:22:11 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
**	Detecte si l'etat est accepteur ou pas
*/

int	is_acceptor(int state)
{
	if (state == DOTCOMMA_V_STATE || state == SPACE_V_STATE
		|| state == LEFT_REDIRECTION_V_STATE
		|| state == RIGHT_REDIRECTION_V_STATE  || state == STAR_STATE
		|| state == LEFT_AGGREGATION_V_STATE
		|| state == RIGHT_AGGREGATION_V_STATE)
		return (TRUE);
	return (FALSE);
}
