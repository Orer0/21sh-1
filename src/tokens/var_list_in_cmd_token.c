/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list_in_cmd_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 04:08:12 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/12 04:11:58 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

t_list		*get_var_list_in_cmd_token(void *token)
{
	if (!(*((t_cmd_token **)(token)))->var_token)
		return (NULL);
	return (get_var_list_token((*((t_cmd_token **)(token)))->var_token));
}
