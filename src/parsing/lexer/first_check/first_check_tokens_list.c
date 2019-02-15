/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check_tokens_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 00:10:05 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/15 23:45:18 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int		not_terminal_type(t_list *lst)
{
	int		type;

	if (!lst)
		return (TRUE);
	type = get_type_token(lst->content);
	if (type == PIPE_TYPE
		|| type == D_QUOTE_TYPE
		|| type == S_QUOTE_TYPE
		|| type == AND_TYPE
		|| type == OR_TYPE)
		return (return_syntax_error(get_token_token(lst->content)));
	return (TRUE);
}

static int		not_started_type(t_list *lst)
{
	int		type;

	if (!lst)
		return (TRUE);
	type = get_type_token(lst->content);
	if (type == PIPE_TYPE
		|| type == DOTCOMMA_TYPE
		|| type == AND_TYPE
		|| type == OR_TYPE
		|| is_redirection(type)
		|| is_aggregation(type))
		return (return_syntax_error(get_token_token(lst->content)));
	return (TRUE);
}

static int		manage_type_next(t_list **tmp, int *end_vars)
{
	if (is_operator(get_type_token((*tmp)->content)))
	{
		if (!first_check_operators(tmp))
			return (FALSE);
		*end_vars = FALSE;
	}
	else if (ft_strchr(get_token_token((*tmp)->content), '=') && !(*end_vars))
	{
		first_check_variables((*tmp));
		*end_vars = TRUE;
	}
	else if (type_cmp(get_type_token((*tmp)->content), NUMBER_TYPE))
		set_type_token((*tmp)->content, WORD_TYPE);
	else
		*end_vars = TRUE;
	return (TRUE);
}

static int		manage_type(t_list **tmp, int *end_vars)
{
	if (is_aggregation(get_type_token((*tmp)->content)))
	{
		if (!first_check_aggregations((*tmp)))
			return (FALSE);
	}
	else if (is_redirection(get_type_token((*tmp)->content)))
	{
		if (!first_check_redirections((*tmp)))
			return (FALSE);
		if (get_type_token((*tmp)->content) == HEREDOC_TYPE)
		{
			if (!(shell_data_singleton()->term))
			{
				ft_fd_printf(2, "21sh: syntax error: unexpected end of file\n");
				quit_shell(EXIT_FAILURE, 0);
			}
			if (!first_check_heredoc(tmp))
				return (FALSE);
		}
	}
	else
		return (manage_type_next(tmp, end_vars));
	return (TRUE);
}

int				first_check_tokens_list(t_list *lst)
{
	t_list		*tmp;
	int			end_vars;

	end_vars = FALSE;
	tmp = lst;
	if (!not_started_type(tmp))
		return (FALSE);
	while (tmp)
	{
		if (!manage_type(&tmp, &end_vars))
			return (FALSE);
		if (tmp->next == NULL)
			return (not_terminal_type(tmp));
		tmp = tmp->next;
	}
	return (TRUE);
}
