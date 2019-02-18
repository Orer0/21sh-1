/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 20:47:47 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/18 22:07:55 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "st.h"

static t_tokens_list	*create_tokens_list_struct(t_list *lst)
{
	t_tokens_list	*result;

	if (!(result = ft_memalloc(sizeof(t_tokens_list))))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	result->index = 0;
	result->size = ft_lstlen(lst);
	result->tokens_list = lst;
	return (result);
}

void					syntax_tree(t_list **tokens_list, t_ptree **tree)
{
	t_tokens_list *tokens_list_struct;

	tokens_list_struct = create_tokens_list_struct(*tokens_list);
	ft_ptree_create_node(tree, NULL, START_TYPE);
	s_rule(&tokens_list_struct, tree);
	ft_memdel((void **)&tokens_list_struct);
}
