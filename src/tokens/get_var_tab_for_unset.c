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
	char	**arr;

	if (!(arr = ft_strsplit(str, '=')))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	name = ft_strdup(arr[0]);
	ft_strtab_del(&arr);
	return (name);
}

char			**get_var_tab_for_unset(t_var_token *token)
{
	char	**arr;
	t_list	*tmp;
	char	*name;

	if (!(arr = ft_memalloc(sizeof(char *) * 2)))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	arr[0] = get_name_of_var(token->token);
	arr[1] = NULL;
	tmp = token->var_lst;
	while (tmp)
	{
		name = get_name_of_var(get_token_token(tmp->content));
		ft_strtab_addend(&arr, name);
		ft_strdel(&name);
		tmp = tmp->next;
	}
	return (arr);
}
