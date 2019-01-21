/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 00:06:35 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/21 01:13:47 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
**	Initialise une structure representant le token
*/

int 	create_token(char *token, int n_state, int l_state, t_token **t)
{
	if (!(*t = ft_memalloc(sizeof(t_token))))
		return (FALSE);
	if (!((*t)->token = ft_strdup(token)))
		return (FALSE);
	(*t)->tab = NULL;
	(*t)->type = get_type_of_token(n_state, l_state);
	return (TRUE);
}
