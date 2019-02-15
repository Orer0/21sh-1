/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manag_ctrl_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroblin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 22:58:28 by aroblin           #+#    #+#             */
/*   Updated: 2019/02/15 23:01:08 by aroblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

char			*ctrl_c(t_term **t)
{
	t_shell_data	*data;

	data = shell_data_singleton();
	data->ctrl_c = TRUE;
	ft_strdel(&(*t)->line);
	(*t)->line = ft_strdup("\n");
	put('\n');
	reset_curse(t);
	return (NULL);
}

