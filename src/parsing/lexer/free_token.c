/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 23:58:18 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/20 23:58:52 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
**	Free un token
*/

void 	free_token(void *content, size_t size)
{
	(void)size;
	ft_strdel(&((*((t_token **)(content)))->token));
	if ((*((t_token **)(content)))->type == COMMAND_TYPE)
		ft_strtab_del(&(*((t_token **)(content)))->tab);
	ft_memdel((void **)((t_token **)(content)));
	ft_memdel(&content);
}
