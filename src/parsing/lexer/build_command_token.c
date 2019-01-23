/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 23:55:46 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/23 20:04:09 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void		add_command_in_tab(char ***tab, t_list *tmp)
{
	if (!(ft_strtab_addend(tab, get_token_token(tmp))))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	if (tmp->prev)
	{
		tmp->prev->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
	}
}

static void		manage_commands(t_list *lst)
{
	char **tab;
	t_list	*tmp;
	t_cmd_token *token;
	t_list	*next;

	tmp = lst;
	if (!(tab = ft_memalloc(sizeof(char *) * 2))
		|| !(tab[0] = ft_strdup(get_token_token(tmp))))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	tmp = tmp->next;
	while (tmp)
	{
		if (is_aggregation(get_type_token(tmp)) || get_type_token(tmp) == HEREDOC_TYPE)
		{
			tmp = tmp->next->next;
			continue ;
		}
		if (get_type_token(tmp) == WORD_TYPE)
		{
			add_command_in_tab(&tab, tmp);
			next = tmp->next;
			ft_lstdelone(&tmp, free_token);
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
	set_tab_token(lst, tab);
}

void 	build_command_token(void)
{
	t_list			*tmp;
	t_shell_data 	*data;
	// t_list			*variables;
	// t_list			*next;

	// variables = NULL;
	data = shell_data_singleton();
	tmp = data->tokens_list;
	if (tmp == NULL)
		return ;
	while (tmp)
	{
		// if (get_type_token(tmp) == VAR_TYPE)
		// {
		// 	if (!variables)
		// 		variables = ft_lstnew(&tmp, sizeof(tmp));
		// 	else
		// 		ft_lstaddend(&variables, ft_lstnew(&tmp, sizeof(tmp)));
		// 	if (tmp->prev)
		// 	{
		// 		tmp->prev->next = tmp->next;
		// 		if (tmp->next)
		// 			tmp->next->prev = tmp->prev;
		// 	}
		// 	next = tmp->next;
		// 	// ft_lstdelone(&tmp, free_token);
		// 	tmp = next;
		// 	continue ;
		// }
		if (get_type_token(tmp) == WORD_TYPE)
		{
			manage_commands(tmp);
			// (*((t_cmd_token **)(tmp->content)))->assign = variables;
		}
		tmp = tmp->next;
	}
}
