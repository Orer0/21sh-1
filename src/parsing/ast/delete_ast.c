/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 06:10:28 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/28 06:52:54 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static void 	free_ast_token(void *data)
{
	ft_memdel(&data);
}

void 		delete_ast(t_btree **ast)
{
	ft_btree_del(ast, free_ast_token);
	*ast = NULL;
}
