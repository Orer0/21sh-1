/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_tab_for_unset.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 04:42:00 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/31 04:57:35 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
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

char 	**get_var_tab_for_unset(t_var_token *token)
{
	char	**tab;
	t_list	*tmp;

	if (!(tab = ft_memalloc(sizeof(char *) * 2)))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	tab[0] = ft_strdup(token->token);
	tab[1] = NULL;
	tmp = token->var_lst;
	while (tmp)
	{
		ft_strtab_addend(&tab, get_token_token(tmp->content));
		tmp = tmp->next;
	}
	return (tab);
}
