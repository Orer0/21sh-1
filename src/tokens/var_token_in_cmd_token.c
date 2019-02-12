/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_token_in_cmd_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 04:08:47 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/12 04:12:47 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

void		set_var_token_in_cmd_token(void *token, void *var)
{
	(*((t_cmd_token **)(token)))->var_token = (t_var_token **)var;
}

t_var_token	*get_var_token_in_cmd_token(void *token)
{
	if (!(*((t_cmd_token **)(token)))->var_token)
		return (NULL);
	return ((*(*((t_cmd_token **)(token)))->var_token));
}
