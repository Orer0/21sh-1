/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 23:41:47 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/10 23:43:39 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		first_check_redirections(t_list *lst)
{
	int		type;

	if (lst->next)
	{
		type = get_type_token(lst->next->content);
		if (type == WORD_TYPE)
		{
			set_type_token(lst->next->content, REDIRECTION_ARG_TYPE);
			return (TRUE);
		}
	}
	return(return_syntax_error(get_token_token(lst->content)));
}
