/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check_operators.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 23:37:30 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/10 23:39:23 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		first_check_operators(t_list **lst)
{
	int		type;
	t_list	*prev;

	if ((*lst)->next)
	{
		type = get_type_token((*lst)->next->content);
		if (is_operator(type))
			return (return_syntax_error(get_token_token((*lst)->content)));
	}
	else
	{
		if (get_type_token((*lst)->content) == DOTCOMMA_TYPE)
		{
			prev = (*lst)->prev;
			ft_lstdelone(lst, free_token);
			*lst = prev;
			(*lst)->next = NULL;
		}
		else if (is_operator(get_type_token((*lst)->content)))
			return (return_syntax_error(get_token_token((*lst)->content)));
	}
	return (TRUE);
}
