/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 23:55:46 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/28 22:48:02 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void		replace_content(t_list *lst)
{
	t_cmd_token *token;

	token_constructor(get_token_token(lst->content), CMD_TYPE, (t_token **)&token);
	free_token(lst->content, 0);
	if (!(lst->content = ft_memalloc(sizeof(&token) * sizeof(t_cmd_token))))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	ft_memcpy(lst->content, &token, sizeof(t_cmd_token));
	lst->content_size = sizeof(t_cmd_token);
}

static void		manage_commands(t_list *lst)
{
	t_list	*args_list;
	t_list	*tmp;

	args_list = NULL;
	tmp = lst->next;
	while (tmp)
	{
		if (is_aggregation(get_type_token(tmp->content))
			|| get_type_token(tmp->content) == HEREDOC_TYPE)
		{
			tmp = tmp->next->next;
			continue ;
		}
		if (get_type_token(tmp->content) == WORD_TYPE)
			put_arg_in_cmd_list(&tmp, &args_list);
		else
			break ;
	}
	replace_content(lst);
	set_args_token(lst->content, args_list);
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
	ft_memdel((void **)&tmp);
}

static void		manage_variables(t_list *lst)
{
	t_list			*next;
	t_shell_data 	*data;

	data = shell_data_singleton();
	set_var_token_in_cmd_token(lst->content,
		((t_var_token **)(lst->prev->content)));
	next = lst->next;
	if (!lst->prev->prev)
		data->tokens_list = data->tokens_list->next;
	ft_lstremoveone(&(lst->prev));
	lst = next;
}

void 	build_command_token(void)
{
	t_list			*tmp;
	t_shell_data 	*data;

	data = shell_data_singleton();
	tmp = data->tokens_list;
	if (tmp == NULL)
		return ;
	while (tmp)
	{
		if (get_type_token(tmp->content) == WORD_TYPE)
		{
			manage_commands(tmp);
			if (tmp->prev)
			{
				if (get_type_token(tmp->prev->content) == VAR_TYPE)
				{
					manage_variables(tmp);
					continue;
				}
			}
		}
		tmp = tmp->next;
	}
}
