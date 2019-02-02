/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check_tokens_list_tools.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 22:50:42 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/02 02:10:32 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
	token->is_expansion = get_expansion_token(lst->content);
	free_token(lst->content, 0);
	if (!(lst->content = ft_memalloc(sizeof(&token) * sizeof(t_var_token))))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	ft_memcpy(lst->content, &token, sizeof(t_var_token));
	lst->content_size = sizeof(t_var_token);
}

void		aggregations(t_list *lst)
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

void		redirections(t_list *lst)
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

void		variables(t_list *lst)
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
