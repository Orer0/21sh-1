/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check_tokens_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 00:10:05 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/10 00:50:40 by ndubouil         ###   ########.fr       */
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
	{
		ft_fd_printf(2, "21sh: syntax error near unexpected token : \"%s\"\n", get_token_token(lst->content));
		return (FALSE);
	}
		// unexpected_token_error(get_token_token(lst->content));
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
	{
		ft_fd_printf(2, "21sh: syntax error near unexpected token : \"%s\"\n", get_token_token(lst->content));
		return (FALSE);
	}
	return (TRUE);
		// unexpected_token_error(get_token_token(lst->content));
}

static int		operators(t_list **lst)
{
	int		type;
	t_list	*prev;

	if ((*lst)->next)
	{
		type = get_type_token((*lst)->next->content);
		if (is_operator(type))
		{
			ft_fd_printf(2, "21sh: syntax error near unexpected token : \"%s\"\n", get_token_token((*lst)->content));
			return (FALSE);
		}
				// unexpected_token_error(get_token_token((*lst)->content));
	}
	else
	{
		if (get_type_token((*lst)->content) == DOTCOMMA_TYPE)
		{
			prev = (*lst)->prev;
			ft_lstdelone(lst, free_token);
			*lst = prev;
			(*lst)->next = NULL;
		}
		else if (is_operator(get_type_token((*lst)->content)))
		{
			ft_fd_printf(2, "21sh: syntax error near unexpected token : \"%s\"\n", get_token_token((*lst)->content));
			return (FALSE);
		}
			// unexpected_token_error(get_token_token((*lst)->content));
	}
	return (TRUE);
}

static int		manage_type(t_list **tmp, int *end_vars)
{
	t_shell_data 	*data;

	data = shell_data_singleton();
	if (is_aggregation(get_type_token((*tmp)->content)))
	{
		if (!aggregations((*tmp)))
			return (FALSE);
	}
	else if (is_redirection(get_type_token((*tmp)->content)))
	{
		if (!redirections((*tmp)))
			return (FALSE);
		if (get_type_token((*tmp)->content) == HEREDOC_TYPE)
		{
			if (!data->term)
			{
				ft_fd_printf(2, "21sh: syntax error: unexpected end of file\n");
				quit_shell(EXIT_FAILURE, 0);
			}
			char	*tmpstr;
			char *str;
			char *line;
			tmpstr = NULL;
			str = NULL;
			line = NULL;
			char *argument = get_token_token((*tmp)->next->content);
			while (!ft_strequ(line, argument))
			{
				ft_strdel(&line);
				line = get_line(PROMPT_MIN);
				if (str && !ft_strequ(line, "\n"))
				{
					tmpstr = str;
					str = ft_strjoin(tmpstr, "\n");
					ft_strdel(&tmpstr);
				}
				if (!ft_strequ(line, argument))
				{
					if (!str)
						str = ft_strdup(line);
					else
					{
						tmpstr = str;
						str = ft_strjoin(tmpstr, line);
						ft_strdel(&tmpstr);
					}
				}
			}
			ft_strdel(&(*((t_token **)((*tmp)->next->content)))->token);
			set_token_token((*tmp)->next->content, str);
			set_expansion_token((*tmp)->next->content, FALSE);
		}
	}
	else if (is_operator(get_type_token((*tmp)->content)))
	{
		if (!operators(tmp))
			return (FALSE);
		*end_vars = FALSE;
	}
	else if (ft_strchr(get_token_token((*tmp)->content), '=') && !(*end_vars))
	{
		variables((*tmp));
		*end_vars = TRUE;
	}
	else if (type_cmp(get_type_token((*tmp)->content), NUMBER_TYPE))
		set_type_token((*tmp)->content, WORD_TYPE);
	else
		*end_vars = TRUE;
	return (TRUE);
}

int 	first_check_tokens_list(t_list *lst)
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
