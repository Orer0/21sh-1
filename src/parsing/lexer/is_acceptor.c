/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_acceptor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 23:26:41 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/23 18:50:49 by ndubouil         ###   ########.fr       */
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
		|| state == VAR_V_STAR_STATE || state == LEFT_AGGREGATION_V_STATE
		|| state == RIGHT_AGGREGATION_V_STATE)
		return (TRUE);
	return (FALSE);
}
