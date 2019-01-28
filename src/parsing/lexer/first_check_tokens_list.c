/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check_tokens_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 00:10:05 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/28 07:30:29 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void		unexpected_token_error(char *token)
{
	ft_printf("syntax error near unexpected token : \"%s\"\n", token);
	quit_shell(EXIT_FAILURE, 0);
}

static void		not_terminal_type(t_list *lst)
{
	int		type;

	if (!lst)
		return ;
	type = get_type_token(lst->content);
	if (type == PIPE_TYPE
		|| type == D_QUOTE_TYPE
		|| type == S_QUOTE_TYPE
		|| type == AND_TYPE
		|| type == OR_TYPE)
		unexpected_token_error(get_token_token(lst->content));
}

static void		not_started_type(t_list *lst)
{
	int		type;

	if (!lst)
		return ;
	type = get_type_token(lst->content);
	if (type == PIPE_TYPE
		|| type == DOTCOMMA_TYPE
		|| type == AND_TYPE
		|| type == OR_TYPE)
		unexpected_token_error(get_token_token(lst->content));
}

static void		aggregations(t_list *lst)
{
	int		type;

	if (lst->next)
	{
		type = get_type_token(lst->next->content);
		if (type == NUMBER_TYPE || type == WORD_TYPE)
		{
			set_type_token(lst->next->content, AGGREGATION_ARG_TYPE);
			return ;
		}
	}
	unexpected_token_error(get_token_token(lst->content));
}

static void		redirections(t_list *lst)
{
	int		type;

	if (lst->next)
	{
		type = get_type_token(lst->next->content);
		if (type == WORD_TYPE)
		{
			set_type_token(lst->next->content, REDIRECTION_ARG_TYPE);
			return ;
		}
	}
	unexpected_token_error(get_token_token(lst));
}

static void 	ft_lstremoveone(t_list	**lst)
{
	t_list	*tmp;

	tmp = *lst;
	if (!tmp)
		return ;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
}

static void		replace_content(t_list *lst)
{
	t_var_token *token;

	token_constructor(get_token_token(lst->content), VAR_TYPE, (t_token **)&token);
	free_token(lst->content, 0);
	if (!(lst->content = ft_memalloc(sizeof(&token) * sizeof(t_var_token))))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	ft_memcpy(lst->content, &token, sizeof(t_var_token));
	lst->content_size = sizeof(t_var_token);
}

static void		variables(t_list *lst)
{
	t_list	*tmp;
	t_list	*next;
	t_list	*var_list;
	t_list	*cpy;

	var_list = NULL;
	tmp = lst->next;
	while (tmp)
	{
		if (!ft_strchr(get_token_token(tmp->content), '='))
			break ;
		next = tmp->next;
		cpy = tmp;
		ft_lstremoveone(&tmp);
		cpy->next = NULL;
		if (!var_list)
			var_list = cpy;
		else
			ft_lstaddend(&var_list, cpy);
		tmp = next;
	}
	replace_content(lst);
	set_var_list_token(lst->content, var_list);
}

static void		operators(t_list *lst)
{
	int		type;

	if (lst->next)
	{
		type = get_type_token(lst->next->content);
		if (is_operator(type))
			unexpected_token_error(get_token_token(lst->content));
	}
	else
	{
		if (is_operator(get_type_token(lst->content)))
			unexpected_token_error(get_token_token(lst->content));
	}
}

static void		manage_type(t_list **tmp, int *end_vars)
{
	if (is_aggregation(get_type_token((*tmp)->content)))
		aggregations((*tmp));
	else if (is_redirection(get_type_token((*tmp)->content)))
		redirections((*tmp));
	else if (is_operator(get_type_token((*tmp)->content)))
	{
		operators((*tmp));
		*end_vars = FALSE;
	}
	else if (ft_strchr(get_token_token((*tmp)->content), '=') && !(*end_vars))
	{
		variables((*tmp));
		*end_vars = TRUE;
	}
	else if (type_cmp(get_type_token((*tmp)->content), NUMBER_TYPE))
		set_type_token((*tmp)->content, WORD_TYPE);
}

void 	first_check_tokens_list(t_list *lst)
{
	t_list		*tmp;
	int			end_vars;

	end_vars = FALSE;
	tmp = lst;
	not_started_type(tmp);
	while (tmp)
	{
		manage_type(&tmp, &end_vars);
		if (tmp->next == NULL)
			return (not_terminal_type(tmp));
		tmp = tmp->next;
	}
}
