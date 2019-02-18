/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_data_singleton.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 07:11:02 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/18 22:27:02 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_shell_data	*shell_data_singleton(void)
{
	static t_shell_data *data;

	if (!data)
	{
		if (!(data = ft_memalloc(sizeof(t_shell_data))))
			exit(EXIT_FAILURE);
	}
	return (data);
}
