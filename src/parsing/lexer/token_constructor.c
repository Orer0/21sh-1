/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_constructor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 03:03:07 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/11 23:33:06 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
**	Initialise une structure representant le token
*/

void	token_constructor(char *token, int type, t_token **t)
{
	if (type == CMD_TYPE)
		*t = ft_memalloc(sizeof(t_cmd_token));
	else if (type == VAR_TYPE)
		*t = ft_memalloc(sizeof(t_var_token));
	else
		*t = ft_memalloc(sizeof(t_token));
	if (!(*t))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	if (!((*t)->token = ft_strdup(token)))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	(*t)->type = type;
}
