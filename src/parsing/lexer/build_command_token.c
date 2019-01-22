/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 23:55:46 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/22 04:28:38 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void		add_command_in_tab(char ***tab, t_list *lst, t_list *tmp)
{
	t_list	*del;

	if (!(ft_strtab_addend(tab, get_token_token(tmp))))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	del = tmp;
	lst->next = tmp->next;
	ft_lstdelone(&del, free_token);
}

static void		manage_commands(t_list *lst)
{
	char **tab;
	t_list	*tmp;
	t_cmd_token *token;

	tmp = lst;
	if (!(tab = ft_memalloc(sizeof(char *) * 2))
		|| !(tab[0] = ft_strdup(get_token_token(tmp))))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	tmp = tmp->next;
	while (tmp)
	{
		// if (is_aggregation(get_type_token(tmp)))
		// {
		// 	if (tmp->next->next)
		// 	{
		// 		tmp = tmp->next->next;
		// 		continue ;
		// 	}
		//
		// }
		if (get_type_token(tmp) == WORD_TYPE)
		{
			add_command_in_tab(&tab, lst, tmp);
			tmp = lst->next;
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

void 	build_command_token(t_list *lst)
{
	t_list		*tmp;

	tmp = lst;
	if (lst == NULL)
		return ;
	while (tmp != NULL)
	{
		if (get_type_token(tmp) == WORD_TYPE)
			manage_commands(tmp);
		tmp = tmp->next;
	}
}
