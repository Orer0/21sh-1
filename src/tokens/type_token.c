/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 04:02:45 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/12 04:12:26 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

void	set_type_token(void *token, int type)
{
	(*((t_token **)(token)))->type = type;
}

int		get_type_token(void *token)
{
	return ((*((t_token **)(token)))->type);
}
