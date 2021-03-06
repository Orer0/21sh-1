/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 04:27:56 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/18 23:55:33 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "tokens.h"

static void		loop_routine(t_var_token **token, t_list *tmp, char ***arr)
{
	if (get_type_token(token) == VAR_TYPE)
	{
		if ((*((t_var_token **)(tmp->content)))->is_expansion)
			manage_expansion_var(&((*((t_var_token **)(tmp->content)))->token));
		ft_strtab_addend(arr, (*((t_var_token **)(tmp->content)))->token);
	}
	else if (get_type_token(token) == CMD_TYPE)
	{
		if (((t_var_token *)(tmp->content))->is_expansion)
			manage_expansion_var(&(((t_var_token *)(tmp->content)))->token);
		ft_strtab_addend(arr, ((t_var_token *)(tmp->content))->token);
	}
}

char			**get_var_tab(t_var_token **token)
{
	char	**arr;
	t_list	*tmp;

	if (get_type_token(token) == VAR_TYPE)
	{
		if (!(arr = ft_memalloc(sizeof(char *) * 2)))
			quit_shell(EXIT_FAILURE, MALLOC_ERR);
		if ((*token)->is_expansion)
			manage_expansion_var(&(*token)->token);
		arr[0] = ft_strdup((*token)->token);
	}
	else
	{
		if (!(arr = ft_memalloc(sizeof(char *))))
			quit_shell(EXIT_FAILURE, MALLOC_ERR);
	}
	tmp = (*token)->var_lst;
	while (tmp)
	{
		loop_routine(token, tmp, &arr);
		tmp = tmp->next;
	}
	return (arr);
}
