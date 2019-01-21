/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtab_del.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 20:34:01 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/20 20:34:25 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strtab_del(char ***tab)
{
	int		i;

	if (!(*tab))
		return ;
	if (!(*tab)[0])
	{
		ft_memdel((void **)tab);
		*tab = NULL;
		return ;
	}
	i = -1;
	while ((*tab)[++i])
		ft_strdel(&(*tab)[i]);
	ft_strdel(&(*tab)[i]);
	ft_memdel((void **)tab);
	*tab = NULL;
}
