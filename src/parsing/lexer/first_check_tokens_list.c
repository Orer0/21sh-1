/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check_tokens_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 00:10:05 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/21 00:25:23 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int		unexpected_token_error(char *token)
{
	ft_printf("syntax error near unexpected token : \"%s\"\n", token);
	return (FALSE);
}

static int		not_terminal_type(t_list *lst)
{
	if ((*((t_token **)(lst->content)))->type == PIPE_TYPE
		|| (*((t_token **)(lst->content)))->type == D_QUOTE_TYPE
		|| (*((t_token **)(lst->content)))->type == S_QUOTE_TYPE)
		return (unexpected_token_error((*((t_token **)(lst->content)))->token));
	else
		return (TRUE);
}

static int		aggregations(t_list *lst)
{
	if (lst->next && ((*((t_token **)(lst->next->content)))->type == NUMBER_TYPE
		|| (*((t_token **)(lst->next->content)))->type == WORD_TYPE))
	{
		(*((t_token **)(lst->next->content)))->type = AGGREGATION_ARG_TYPE;
		return (TRUE);
	}
	return (unexpected_token_error((*((t_token **)(lst->content)))->token));
}

static int		redirections(t_list *lst)
{
	if (lst->next && (*((t_token **)(lst->next->content)))->type == WORD_TYPE)
	{
		(*((t_token **)(lst->next->content)))->type = REDIRECTION_ARG_TYPE;
		return (TRUE);
	}
	return (unexpected_token_error((*((t_token **)(lst->content)))->token));
}

int 	first_check_tokens_list(t_list *lst)
{
	t_list		*tmp;

	tmp = lst;
	if (lst == NULL)
		return (0);
	if ((*((t_token **)(tmp->content)))->type == DOTCOMMA_TYPE
		|| (*((t_token **)(tmp->content)))->type == PIPE_TYPE)
		return (unexpected_token_error((*((t_token **)(tmp->content)))->token));
	while (tmp != NULL)
	{
		if ((*((t_token **)(tmp->content)))->type == AGGREGATION_TYPE)
			return (aggregations(tmp));
		else if ((*((t_token **)(tmp->content)))->type == REDIRECTION_TYPE)
			return (redirections(tmp));
		else if (((*((t_token **)(tmp->content)))->token)[0] == '~')
		{
			replace_tilde(&(*((t_token **)(tmp->content)))->token);
			(*((t_token **)(tmp->content)))->type = WORD_TYPE;
		}
		if (tmp->next == NULL)
			return (not_terminal_type(tmp));
		tmp = tmp->next;
	}
	return (TRUE);
}
