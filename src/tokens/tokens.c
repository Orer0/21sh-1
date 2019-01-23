/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 00:06:35 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/22 19:42:13 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

void 	set_type_token(t_list *lst, int type)
{
	(*((t_token **)(lst->content)))->type = type;
}

int 	get_type_token(t_list *lst)
{
	return ((*((t_token **)(lst->content)))->type);
}

char 	*get_token_token(t_list *lst)
{
	return ((*((t_token **)(lst->content)))->token);
}

void 	set_tab_token(t_list *lst, char **tab)
{
	(*((t_cmd_token **)(lst->content)))->tab = tab;
}

char 	**get_tab_token(t_list *lst)
{
	return ((*((t_cmd_token **)(lst->content)))->tab);
}
