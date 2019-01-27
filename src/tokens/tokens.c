/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 00:06:35 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/27 02:09:40 by ndubouil         ###   ########.fr       */
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

void 	set_type_token(void *token, int type)
{
	(*((t_token **)(token)))->type = type;
}

void 	set_expansion_token(void *token, int expansion)
{
	(*((t_token **)(token)))->is_expansion = expansion;
}

int 	get_expansion_token(void *token)
{
	return ((*((t_token **)(token)))->is_expansion);
}

int 	get_type_token(void *token)
{
	return ((*((t_token **)(token)))->type);
}

void 	set_token_token(void *token, char *str)
{
	(*((t_token **)(token)))->token = str;
}

char 	*get_token_token(void *token)
{
	return ((*((t_token **)(token)))->token);
}

void 	set_var_list_token(void *token, t_list *vars)
{
	(*((t_var_token **)(token)))->var_lst = vars;
}

t_list 	*get_var_list_token(void *token)
{
	return ((*((t_var_token **)(token)))->var_lst);
}

void 	set_args_token(void *token, t_list *args)
{
	(*((t_cmd_token **)(token)))->args = args;
}

t_list 	*get_var_list_in_cmd_token(void *token)
{
	return (get_var_list_token((*((t_cmd_token **)(token)))->var_token));
}

t_list 	*get_args_token(void *token)
{
	return ((*((t_cmd_token **)(token)))->args);
}
