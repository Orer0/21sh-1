/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check_tokens_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 00:10:05 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/23 05:27:33 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void		unexpected_token_error(char *token)
{
	ft_printf("syntax error near unexpected token : \"%s\"\n", token);
	quit_shell(EXIT_FAILURE, 0);
}

static void		not_terminal_type(t_list *lst)
{
	int		type;

	type = get_type_token(lst);
	if (type == PIPE_TYPE || type == D_QUOTE_TYPE || type == S_QUOTE_TYPE)
		unexpected_token_error(get_token_token(lst));
}

static void		aggregations(t_list *lst)
{
	int		type;

	if (lst->next)
	{
		type = get_type_token(lst->next);
		if (type == NUMBER_TYPE || type == WORD_TYPE)
		{
			set_type_token(lst->next, AGGREGATION_ARG_TYPE);
			return ;
		}
	}
	unexpected_token_error(get_token_token(lst));
}

static void		redirections(t_list *lst)
{
	int		type;

	if (lst->next)
	{
		type = get_type_token(lst->next);
		if (type == WORD_TYPE)
		{
			set_type_token(lst->next, REDIRECTION_ARG_TYPE);
			return ;
		}
	}
	unexpected_token_error(get_token_token(lst));
}

void 	first_check_tokens_list(t_list *lst)
{
	t_list		*tmp;

	tmp = lst;
	if (lst == NULL)
		return ;
	if (get_type_token(tmp) == DOTCOMMA_TYPE
		|| get_type_token(tmp) == PIPE_TYPE)
		return (unexpected_token_error(get_token_token(tmp)));
	while (tmp != NULL)
	{
		if (is_aggregation(get_type_token(tmp)))
			aggregations(tmp);
		else if (is_redirection(get_type_token(tmp)))
			redirections(tmp);
		else if (get_token_token(tmp)[0] == '~')
		{
			replace_tilde(&(*((t_token **)(tmp->content)))->token);
			set_type_token(tmp, WORD_TYPE);
		}
		else if (get_type_token(tmp) == NUMBER_TYPE)
			set_type_token(tmp, WORD_TYPE);
		if (tmp->next == NULL)
			return (not_terminal_type(tmp));
		tmp = tmp->next;
	}
}
