/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ignored.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 23:28:19 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/20 23:28:29 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
**	Detecte si l'etat est ignoré
*/

int	is_ignored(int current, int state)
{
	if ((current == START_STATE && state == D_QUOTE_STATE)
		|| (current == CHAR_STATE && state == D_QUOTE_STATE)
		|| (current == NUMBER_STATE && state == D_QUOTE_STATE)
		|| (current == TILDE_STATE && state == D_QUOTE_STATE)
		|| (current == END_D_QUOTE_STATE && state == D_QUOTE_STATE)
		|| (current == END_S_QUOTE_STATE && state == D_QUOTE_STATE)
		|| (current == START_STATE && state == S_QUOTE_STATE)
		|| (current == CHAR_STATE && state == S_QUOTE_STATE)
		|| (current == NUMBER_STATE && state == S_QUOTE_STATE)
		|| (current == TILDE_STATE && state == S_QUOTE_STATE)
		|| (current == END_D_QUOTE_STATE && state == S_QUOTE_STATE)
		|| (current == END_S_QUOTE_STATE && state == S_QUOTE_STATE)
		|| (current == START_STATE && state == START_STATE)
		|| state == END_D_QUOTE_STATE
		|| state == END_S_QUOTE_STATE
		|| (current == BACKSLASH_D_QUOTE_STATE && state == D_QUOTE_STATE)
		|| state == BACKSLASH_STATE)
		return (TRUE);
	return (FALSE);
}
