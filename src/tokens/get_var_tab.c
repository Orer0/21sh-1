/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 04:27:56 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/12 03:51:52 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "tokens.h"

char		**get_var_tab(t_var_token **token)
{
	char	**tab;
	t_list	*tmp;

	if (get_type_token(token) == VAR_TYPE)
	{
		if (!(tab = ft_memalloc(sizeof(char *) * 2)))
			quit_shell(EXIT_FAILURE, MALLOC_ERR);
		if ((*token)->is_expansion)
			manage_expansion_var(&(*token)->token);
		tab[0] = ft_strdup((*token)->token);
	}
	else
	{
		if (!(tab = ft_memalloc(sizeof(char *))))
			quit_shell(EXIT_FAILURE, MALLOC_ERR);
	}
	tmp = (*token)->var_lst;
	while (tmp)
	{
		if (((t_var_token *)(tmp->content))->is_expansion)
			manage_expansion_var(&((t_var_token *)(tmp->content))->token);
		ft_strtab_addend(&tab, ((t_var_token *)(tmp->content))->token);
		tmp = tmp->next;
	}
	return (tab);
}
