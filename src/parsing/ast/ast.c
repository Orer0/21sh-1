/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 22:59:58 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/10 05:26:15 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/*
**	Generate the AST with the syntax tree
*/

static void		generate_ast(t_ptree **tree)
{
	t_list		*tmp;

	if (!tree)
		return ;
	tmp = (*tree)->childs_lst;
	while (tmp)
	{
		generate_ast(((t_ptree **)(tmp->content)));
		tmp = tmp->next;
	}
	execute_post_order_procedure(tree);
}

/*
**	Build and return the AST
*/

t_btree			*get_ast(t_ptree **parsing_tree)
{
	generate_ast(parsing_tree);
	return ((*parsing_tree)->ast);
}
