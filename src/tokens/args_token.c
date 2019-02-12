/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 04:05:46 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/12 04:10:53 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

void	set_args_token(void *token, t_list *args)
{
	(*((t_cmd_token **)(token)))->args = args;
}

t_list	*get_args_token(void *token)
{
	return ((*((t_cmd_token **)(token)))->args);
}
