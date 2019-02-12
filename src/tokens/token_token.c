/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 04:04:45 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/12 04:11:47 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

void	set_token_token(void *token, char *str)
{
	(*((t_token **)(token)))->token = str;
}

char	*get_token_token(void *token)
{
	return ((*((t_token **)(token)))->token);
}
