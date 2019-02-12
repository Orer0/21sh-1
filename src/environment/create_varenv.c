/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_varenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 00:18:42 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/13 00:14:46 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_varenv	*create_varenv(char *name, char *content)
{
	t_varenv	*varenv;

	if (!(varenv = ft_memalloc(sizeof(t_varenv))))
		return (NULL);
	if (!(varenv->name = ft_strdup(name)))
		return (NULL);
	if (!content || !content[0])
	{
		if (!(varenv->content = ft_strdup("")))
			return (NULL);
	}
	else
	{
		if (!(varenv->content = ft_strdup(content)))
			return (NULL);
	}
	return (varenv);
}
