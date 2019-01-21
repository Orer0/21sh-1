/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 23:55:46 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/21 03:30:42 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int		manage_commands(t_list *lst)
{
	char **tab;
	t_list	*tmp;
	t_list	*del;

	tmp = lst;
	tab = ft_memalloc(sizeof(char *) * 2);
	tab[0] = ft_strdup((*((t_token **)(tmp->content)))->token);
	tmp = tmp->next;
	while (tmp)
	{
		if ((*((t_token **)(tmp->content)))->type == WORD_TYPE)
		{
			ft_strtab_addend(&tab, (*((t_token **)(tmp->content)))->token);
			del = tmp;
			lst->next = tmp->next;
			tmp = lst->next;
			ft_lstdelone(&del, free_token);
		}
		else
			break ;
	}
	(*((t_token **)(lst->content)))->type = COMMAND_TYPE;
	(*((t_token **)(lst->content)))->tab = tab;
	return (TRUE);
}

int 	build_command_token(t_list *lst)
{
	t_list		*tmp;

	tmp = lst;
	if (lst == NULL)
		return (0);
	while (tmp != NULL)
	{
		if ((*((t_token **)(tmp->content)))->type == WORD_TYPE)
		{
			manage_commands(tmp);
		}
		tmp = tmp->next;
	}
	return (TRUE);
}
