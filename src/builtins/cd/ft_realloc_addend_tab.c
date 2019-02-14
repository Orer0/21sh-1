/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_addend_tab.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 19:41:33 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/29 08:30:20 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		ft_realloc_addend_tab(char ***arr, char *elem)
{
	int		i;
	char	**tmp;

	if (*arr == NULL || !elem)
		return (FALSE);
	i = -1;
	while ((*arr)[++i])
		;
	if (!(tmp = ft_memalloc((i + 2) * sizeof(char *))))
		return (FALSE);
	i = -1;
	while ((*arr)[++i])
		if (!(tmp[i] = ft_strdup((*arr)[i])))
			return (FALSE);
	if (!(tmp[i] = ft_strdup(elem)))
		return (FALSE);
	tmp[i + 1] = NULL;
	ft_strtab_del(arr);
	*arr = tmp;
	return (TRUE);
}
