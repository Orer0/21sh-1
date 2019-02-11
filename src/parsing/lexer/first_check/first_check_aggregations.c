/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check_aggregations.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 23:44:10 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/10 23:45:06 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		first_check_aggregations(t_list *lst)
{
	int		type;

	if (lst->next)
	{
		type = get_type_token(lst->next->content);
		if (type == NUMBER_TYPE || type == WORD_TYPE)
		{
			set_type_token(lst->next->content, AGGREGATION_ARG_TYPE);
			return (TRUE);
		}
	}
	return (return_syntax_error(get_token_token(lst->content)));
}
