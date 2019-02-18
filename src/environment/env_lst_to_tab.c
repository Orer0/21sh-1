/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_to_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 02:28:18 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/18 22:16:51 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void		del_tab(char ***arr)
{
	int		i;

	i = 0;
	while ((*arr)[i++])
		ft_strdel(&(*arr)[i]);
	*arr = NULL;
}

static int		cpy_tab(t_list *lst, char ***arr)
{
	int		i;
	char	*tmp;

	i = 0;
	while (lst)
	{
		if (!((*arr)[i] = ft_strjoin(((t_varenv *)((lst)->content))->name
			, "=")))
			return (FALSE);
		if (((t_varenv *)((lst)->content))->content)
		{
			tmp = (*arr)[i];
			if (!((*arr)[i] = ft_strjoin((*arr)[i]
				, ((t_varenv *)((lst)->content))->content)))
				return (FALSE);
			ft_strdel(&tmp);
		}
		lst = lst->next;
		i++;
	}
	(*arr)[i] = NULL;
	return (TRUE);
}

int				env_lst_to_tab(t_list **lst, char ***arr)
{
	t_list	*node;

	if (*arr != NULL)
		del_tab(arr);
	node = *lst;
	if (*arr == NULL)
		if (!(*arr = ft_memalloc(sizeof(char *) * (ft_lstlen(*lst) + 1))))
			quit_shell(EXIT_FAILURE, MALLOC_ERR);
	if (node != NULL)
		if (!cpy_tab(node, arr))
			return (FALSE);
	return (TRUE);
}
