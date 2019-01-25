/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 23:55:46 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/25 03:40:01 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void		manage_commands(t_list *lst)
{
	t_list	*args_list;
	t_list	*tmp;
	t_cmd_token *token;
	t_list	*next;
	t_list	*cpy;

	args_list = NULL;
	tmp = lst->next;
	while (tmp)
	{
		if (is_aggregation(get_type_token(tmp)) || get_type_token(tmp) == HEREDOC_TYPE)
		{
			tmp = tmp->next->next;
			continue ;
		}
		if (get_type_token(tmp) == WORD_TYPE)
		{
			next = tmp->next;
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			cpy = tmp;
			cpy->next = NULL;
			if (!args_list)
				args_list = cpy;
			else
				ft_lstaddend(&args_list, cpy);
			tmp = next;
		}
		else
			break ;
	}
	token_constructor(get_token_token(lst), CMD_TYPE, (t_token **)&token);
	free_token(lst->content, 0);
	lst->content = ft_memalloc(sizeof(&token) * sizeof(t_cmd_token));
	ft_memcpy(lst->content, &token, sizeof(t_cmd_token));
	lst->content_size = sizeof(t_cmd_token);
	set_args_token(lst, args_list);
}

void 	build_command_token(void)
{
	t_list			*tmp;
	t_shell_data 	*data;
	// t_var_token			*t;
	// t_list			*del;
	// t_list			*tmpp;
	// t_list			*new;

	data = shell_data_singleton();
	tmp = data->tokens_list;
	if (tmp == NULL)
		return ;
	while (tmp)
	{
		if (get_type_token(tmp) == WORD_TYPE)
		{
			manage_commands(tmp);
			if (tmp->prev)
			{
				if (get_type_token(tmp->prev) == VAR_TYPE)
				{
					(*((t_cmd_token **)(tmp->content)))->variables = (*((t_var_token **)(tmp->prev->content)));
					ft_lstremoveone(&(tmp->prev), NULL);
					// tmpp = tmp->prev;
					// while (tmpp && get_type_token(tmpp) == VAR_TYPE)
					// {
					// 	token_constructor((*((t_token **)(tmpp->content)))->token, (*((t_token **)(tmpp->content)))->type, (t_token **)&t);
					// 	new = ft_lstnew(&t, sizeof(t_var_token));
					// 	set_value_token(new, ft_strdup((*((t_var_token **)(tmpp->content)))->value));
					// 	if (!(*((t_cmd_token **)(tmp->content)))->assign)
					// 		(*((t_cmd_token **)(tmp->content)))->assign = new;
					// 	else
					// 		ft_lstadd(&((*((t_cmd_token **)(tmp->content)))->assign), new);
					// 	if (!tmpp->prev)
					// 		break ;
					// 	if (tmpp->prev)
					// 		tmpp->prev->next = tmpp->next;
					// 	if (tmpp->next)
					// 		tmpp->next->prev = tmpp->prev;
					// 	del = tmpp;
					// 	tmpp = tmpp->prev;
					// 	ft_lstdelone(&del, free_token);
					// }
					// if (tmpp == data->tokens_list)
					// {
					// 	del = data->tokens_list;
					// 	data->tokens_list = data->tokens_list->next;
					// 	ft_lstdelone(&del, free_token);
					// }
					// tmp->prev = NULL;
				}
			}
		}
		tmp = tmp->next;
	}
}
