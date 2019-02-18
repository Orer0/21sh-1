/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_varenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 00:18:42 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/18 22:13:00 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_varenv	*create_varenv(char *name, char *content)
{
	t_varenv	*varenv;

	if (!(varenv = ft_memalloc(sizeof(t_varenv))))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	if (!(varenv->name = ft_strdup(name)))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	if (!content)
	{
		if (!(varenv->content = ft_strdup("")))
			quit_shell(EXIT_FAILURE, MALLOC_ERR);
	}
	else
	{
		if (!(varenv->content = ft_strdup(content)))
			quit_shell(EXIT_FAILURE, MALLOC_ERR);
	}
	return (varenv);
}
