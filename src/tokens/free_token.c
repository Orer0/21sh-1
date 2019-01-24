/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 23:58:18 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/24 02:41:39 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
**	Free un token
*/

void 	free_token(void *content, size_t size)
{
	int type;

	type = (*((t_token **)(content)))->type;
	(void)size;
	ft_strdel(&((*((t_token **)(content)))->token));
	if (type == CMD_TYPE)
	{
		ft_strtab_del(&(*((t_cmd_token **)(content)))->tab);
		ft_lstdel(&(*((t_cmd_token **)(content)))->assign, free_token);
	}
	if (type == VAR_TYPE)
		ft_strdel(&(*((t_var_token **)(content)))->value);
	ft_memdel((void **)((t_token **)(content)));
	ft_memdel(&content);
}
