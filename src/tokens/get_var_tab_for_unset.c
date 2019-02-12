/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_tab_for_unset.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 04:42:00 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/31 17:40:15 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "tokens.h"

static char		*get_name_of_var(char *str)
{
	char	*name;
	char	**tab;

	if (!(tab = ft_strsplit(str, '=')))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	name = ft_strdup(tab[0]);
	ft_strtab_del(&tab);
	return (name);
}

char			**get_var_tab_for_unset(t_var_token *token)
{
	char	**tab;
	t_list	*tmp;
	char	*name;

	if (!(tab = ft_memalloc(sizeof(char *) * 2)))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	tab[0] = get_name_of_var(token->token);
	tab[1] = NULL;
	tmp = token->var_lst;
	while (tmp)
	{
		name = get_name_of_var(get_token_token(tmp->content));
		ft_strtab_addend(&tab, name);
		ft_strdel(&name);
		tmp = tmp->next;
	}
	return (tab);
}
