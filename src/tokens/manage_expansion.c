/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 04:31:34 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/02 21:18:39 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "tokens.h"

void	manage_expansion(char **str)
{
	int		i;

	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] == '~')
		{
			ft_printf("retour replace_tilde [%d]\n", replace_tilde(str));
		}
		// if ((*str)[i] == '$')
	}
}
