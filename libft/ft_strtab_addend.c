/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtab_addend.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 20:32:48 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/20 20:40:18 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strtab_addend(char ***tab, char *elem)
{
	int		i;
	char	**tmp;

	if (*tab == NULL || !elem)
		return (0);
	i = -1;
	while ((*tab)[++i])
		;
	if (!(tmp = ft_memalloc((i + 2) * sizeof(char *))))
		return (0);
	i = -1;
	while ((*tab)[++i])
		if (!(tmp[i] = ft_strdup((*tab)[i])))
			return (0);
	if (!(tmp[i] = ft_strdup(elem)))
		return (0);
	tmp[i + 1] = NULL;
	ft_strtab_del(tab);
	*tab = tmp;
	return (1);
}
