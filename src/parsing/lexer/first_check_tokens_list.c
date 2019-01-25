/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check_tokens_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 00:10:05 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/25 18:35:55 by ndubouil         ###   ########.fr       */
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
	if (type == PIPE_TYPE
		|| type == D_QUOTE_TYPE
		|| type == S_QUOTE_TYPE
		|| type == AND_TYPE
		|| type == OR_TYPE)
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

void 	ft_lstremoveone(t_list	**lst, void (*del)(void *, size_t))
{
	t_list	*tmp;

	ft_printf("test = %s\n", get_token_token(*lst));
	tmp = *lst;
	if (!tmp)
		return ;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	(void)del;
	// ft_lstdelone(&tmp, del);
}

static t_var_token		*variables(t_list *lst)
{
	int		type;
	char	*value;

	if (!lst->next)
		return (NULL);
	type = get_type_token(lst->next);
	if (type != WORD_TYPE)
		return (NULL);
	if (get_token_token(lst->next)[0] == '=')
	{
		value = get_token_token(lst->next);
		set_value_token(lst, ft_strdup(&(value[1])));
		ft_lstremoveone(&(lst->next), free_token);
	}
	if (lst->next)
	{
		if (get_type_token(lst->next) == VAR_TYPE)
		{
			(*((t_var_token **)(lst->content)))->next = variables(lst->next);
			ft_lstremoveone(&(lst->next), NULL);
			// ft_memdel((void **)&lst->next);
		}
	}
	return ((*((t_var_token **)(lst->content))));
}

static void		operators(t_list *lst)
{
	int		type;

	if (lst->next)
	{
		type = get_type_token(lst->next);
		if (is_operator(type))
			unexpected_token_error(get_token_token(lst));
	}
	else
	{
		if (is_operator(get_type_token(lst)))
			unexpected_token_error(get_token_token(lst));
	}
}



void 	first_check_tokens_list(t_list *lst)
{
	t_list		*tmp;
	int			t;

	tmp = lst;
	if (lst == NULL)
		return ;
	t = get_type_token(tmp);
	if (t == DOTCOMMA_TYPE || t == PIPE_TYPE || t == AND_TYPE || t == OR_TYPE)
		return (unexpected_token_error(get_token_token(tmp)));
	while (tmp)
	{
		ft_printf("TEST [%s]\n", get_token_token(tmp));
		!is_aggregation(get_type_token(tmp)) ?0: aggregations(tmp);
		!is_redirection(get_type_token(tmp)) ?0: redirections(tmp);
		!(get_type_token(tmp) == VAR_TYPE) ?0: (void)variables(tmp);
		!is_operator(get_type_token(tmp)) ?0: operators(tmp);
		!(get_token_token(tmp)[0] == '~') ?0: set_expansion_token(tmp, TRUE);
		!(get_type_token(tmp) == NUMBER_TYPE) ?0: set_type_token(tmp, WORD_TYPE);
		if (tmp->next == NULL)
			return (not_terminal_type(tmp));
		tmp = tmp->next;
	}
}
