/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 04:03:52 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/12 04:11:28 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

void	set_expansion_token(void *token, int expansion)
{
	(*((t_token **)(token)))->is_expansion = expansion;
}

int		get_expansion_token(void *token)
{
	return ((*((t_token **)(token)))->is_expansion);
}
