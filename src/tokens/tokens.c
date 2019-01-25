/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 00:06:35 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/25 02:08:01 by ndubouil         ###   ########.fr       */
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

int		is_operator(int type)
{
	if (type == DOTCOMMA_TYPE || type == PIPE_TYPE || type == AND_TYPE || type == OR_TYPE)
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

void 	set_expansion_token(t_list *lst, int expansion)
{
	(*((t_token **)(lst->content)))->is_expansion = expansion;
}

int 	get_expansion_token(t_list *lst)
{
	return ((*((t_token **)(lst->content)))->is_expansion);
}

void 	set_value_token(t_list *lst, char *value)
{
	(*((t_var_token **)(lst->content)))->value = value;
}

char 	*get_value_token(t_list *lst)
{
	return ((*((t_var_token **)(lst->content)))->value);
}

int 	get_type_token(t_list *lst)
{
	return ((*((t_token **)(lst->content)))->type);
}

char 	*get_token_token(t_list *lst)
{
	return ((*((t_token **)(lst->content)))->token);
}

void 	set_args_token(t_list *lst, t_list *args)
{
	(*((t_cmd_token **)(lst->content)))->args = args;
}

t_list 	*get_args_token(t_list *lst)
{
	return ((*((t_cmd_token **)(lst->content)))->args);
}


// void 	set_tab_token(t_list *lst, char **tab)
// {
// 	(*((t_cmd_token **)(lst->content)))->tab = tab;
// }
//
// char 	**get_tab_token(t_list *lst)
// {
// 	return ((*((t_cmd_token **)(lst->content)))->tab);
// }
