/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 04:05:20 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/12 04:12:12 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

void	set_var_list_token(void *token, t_list *vars)
{
	(*((t_var_token **)(token)))->var_lst = vars;
}

t_list	*get_var_list_token(void *token)
{
	return ((*((t_var_token **)(token)))->var_lst);
}
