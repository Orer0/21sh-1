/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_parsing_tree.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 05:38:13 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/28 05:38:17 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "st.h"

/*
**	FREE
*/

void 	free_ptree_node(t_ptree **tree)
{
	if (!(*tree))
		return ;
	ft_lstdel(&((*tree)->childs_lst), del_ptree_node);
	ft_memdel((void **)tree);
}


void 	del_ptree_node(void *content, size_t size)
{
	(void)size;
	if (!content)
		return ;
	// Free un child
	ft_lstdel(&(*((t_ptree **)(content)))->childs_lst, del_ptree_node);
	free_ptree_node(((t_ptree **)(content)));
	ft_memdel(&content);
}

/*
**	Delete proprement l'arbre de syntaxe
*/

void 	delete_parsing_tree(t_ptree **tree)
{
	free_ptree_node(tree);
	*tree = NULL;
}
