/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_token_tools.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 22:47:18 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/10 05:51:51 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void		put_arg_in_cmd_list(t_list **lst, t_list **args_list)
{
	t_list	*next;
	t_list	*cpy;

	next = (*lst)->next;
	if ((*lst)->prev)
		(*lst)->prev->next = (*lst)->next;
	if ((*lst)->next)
		(*lst)->next->prev = (*lst)->prev;
	cpy = (*lst);
	cpy->next = NULL;
	if (!(*args_list))
		*args_list = cpy;
	else
		ft_lstaddend(args_list, cpy);
	*lst = next;
}
