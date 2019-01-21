/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_list_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 00:26:32 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/21 00:26:48 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
**	Delete proprement la liste des tokens
*/

void 	delete_list_tokens(t_list **tokens_list)
{
	ft_lstdel(tokens_list, free_token);
}
