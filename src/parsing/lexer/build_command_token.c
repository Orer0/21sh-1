/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 23:55:46 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/26 18:27:11 by ndubouil         ###   ########.fr       */
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

void 	ft_lstremoveone2(t_list	**lst)
{
	t_list	*tmp;

	tmp = *lst;
	if (!tmp)
		return ;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	// ft_strdel(&(*((t_var_token **)(tmp->content)))->token);
	// ft_strdel(&(*((t_var_token **)(tmp->content)))->value);
	// ft_memdel(&tmp->content);
	// ft_memdel((void **)lst);
	// tmp->prev = NULL;
	// tmp->next = NULL;
	// (void)del;
	ft_memdel((void **)&tmp);
}

void 	build_command_token(void)
{
	t_list			*tmp;
	t_shell_data 	*data;
	t_list *next;
	// t_var_token			*tmpp;
	// t_var_token			*new;
	// t_list			*start;

	data = shell_data_singleton();
	tmp = data->tokens_list;
	if (tmp == NULL)
		return ;
	// start = tmp;
	while (tmp)
	{
		if (get_type_token(tmp) == WORD_TYPE)
		{
			manage_commands(tmp);
			if (tmp->prev)
			{
				if (get_type_token(tmp->prev) == VAR_TYPE)
				{
					// tmpp = (*((t_var_token **)(tmp->prev->content)));
					// tmpp->prev = NULL;
					// tmpp->next = NULL;
					// token_constructor((*((t_var_token **)(tmp->prev->content)))->token, (*((t_var_token **)(tmp->prev->content)))->type, (t_token **)&new);
					// new->vars = (*((t_var_token **)(tmp->prev->content)))->vars;
					// new->value = ft_strdup((*((t_var_token **)(tmp->prev->content)))->value);
					// (*((t_var_token **)(tmpp)))->next_vars = NULL;
					(*((t_cmd_token **)(tmp->content)))->variables = ((t_var_token **)(tmp->prev->content));
					next = tmp->next;
					if (!tmp->prev->prev)
						data->tokens_list = data->tokens_list->next;
					ft_lstremoveone2(&(tmp->prev));
					tmp = next;
					continue;
					// ft_memcpy((*((t_cmd_token **)(tmp->content)))->variables, (*((t_var_token **)(tmpp->content))), sizeof(sizeof(t_var_token)));
					// (*((t_cmd_token **)(tmp->content)))->variables = (*((t_var_token **)(tmpp->content)));
					// ft_memdel((void **)&tmpp);
					// (*((t_cmd_token **)(tmp->content)))->variables->prev = NULL;
					// tmpp = (*((t_cmd_token **)(tmp->content)))->variables;
					// ft_printf("TEST ICI = %s\n", get_token_token((*((t_cmd_token **)(tmp->content)))->variables->next));
					// (*((t_cmd_token **)(tmp->content)))->variables->next = NULL;
				}
			}
		}
		tmp = tmp->next;
	}
}
