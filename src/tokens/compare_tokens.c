/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 04:01:26 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/12 04:02:25 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

int		is_redirection(int type)
{
	if (type == IN_RDIR_TYPE || type == OUT_RDIR_TYPE || type == OUT_ARDIR_TYPE
		|| type == HEREDOC_TYPE)
		return (TRUE);
	return (FALSE);
}

int		is_aggregation(int type)
{
	if (type == DUP_IN_FD_TYPE || type == DUP_OUT_FD_TYPE)
		return (TRUE);
	return (FALSE);
}

int		is_operator(int type)
{
	if (type == DOTCOMMA_TYPE || type == PIPE_TYPE
		|| type == AND_TYPE || type == OR_TYPE)
		return (TRUE);
	return (FALSE);
}

int		type_cmp(int first, int second)
{
	if (first == second)
		return (TRUE);
	else if (is_redirection(first) && second == REDIRECTION_TYPE)
		return (TRUE);
	else if (is_redirection(second) && first == REDIRECTION_TYPE)
		return (TRUE);
	else if (is_aggregation(first) && second == AGGREGATION_TYPE)
		return (TRUE);
	else if (is_aggregation(second) && first == AGGREGATION_TYPE)
		return (TRUE);
	return (FALSE);
}
