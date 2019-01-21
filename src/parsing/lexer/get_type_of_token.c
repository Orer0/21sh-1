/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type_of_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 00:01:53 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/21 00:04:44 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int			get_type_of_token_2(int next_state, int last_state)
{
	if (last_state == LEFT_REDIRECTION_STATE
		|| last_state == RIGHT_REDIRECTION_STATE
		|| last_state == DOUBLE_LEFT_REDIRECTION_STATE
		|| last_state == DOUBLE_RIGHT_REDIRECTION_STATE
		|| next_state == LEFT_REDIRECTION_STATE
		|| next_state == RIGHT_REDIRECTION_STATE
		|| next_state == DOUBLE_LEFT_REDIRECTION_STATE
		|| next_state == DOUBLE_RIGHT_REDIRECTION_STATE)
		return (REDIRECTION_TYPE);
	else if (last_state == TILDE_STATE || next_state == TILDE_STATE)
		return (TILDE_TYPE);
	else if (last_state == D_QUOTE_STATE || next_state == D_QUOTE_STATE)
		return (D_QUOTE_TYPE);
	else if (last_state == S_QUOTE_STATE || next_state == S_QUOTE_STATE)
		return (S_QUOTE_TYPE);
	return (NONE_TYPE);
}

/*
**	Retourne le type du token
*/

int			get_type_of_token(int next_state, int last_state)
{
	if (last_state == NUMBER_STATE || next_state == NUMBER_STATE)
		return (NUMBER_TYPE);
	else if (last_state == CHAR_STATE || next_state == CHAR_STATE
		|| last_state == END_D_QUOTE_STATE || next_state == END_D_QUOTE_STATE
		|| last_state == END_S_QUOTE_STATE || next_state == END_S_QUOTE_STATE
		|| last_state == DOLLAR_STATE || next_state == DOLLAR_STATE)
		return (WORD_TYPE);
	else if (last_state == PIPE_V_STATE || next_state == PIPE_V_STATE)
		return (PIPE_TYPE);
	else if (last_state == DOTCOMMA_V_STATE || next_state == DOTCOMMA_V_STATE)
		return (DOTCOMMA_TYPE);
	else if (last_state == LEFT_AGGREGATION_V_STATE
		|| last_state ==  RIGHT_AGGREGATION_V_STATE
		|| next_state == LEFT_AGGREGATION_V_STATE
		|| next_state ==  RIGHT_AGGREGATION_V_STATE)
		return (AGGREGATION_TYPE);
	return (get_type_of_token_2(next_state, last_state));
}
