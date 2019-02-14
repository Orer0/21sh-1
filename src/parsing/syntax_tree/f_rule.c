/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_rule.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 05:59:39 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/13 18:56:30 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "st.h"

int		f_rule(t_tokens_list **tokens_list_struct, t_ptree **tree)
{
	int			id;
	int			save_index;
	t_ptree		**tmp;

	id = ft_ptree_add_child(tree, NULL, F_RULE);
	tmp = ft_ptree_get_node_with_id(tree, id);
	save_index = (*tokens_list_struct)->index;
	if (test_current_token(tokens_list_struct, CMD_TYPE, tmp))
	{
		return (TRUE);
	}
	(*tokens_list_struct)->index = save_index;
	ft_ptree_remove_node_with_id(tree, id);
	id = ft_ptree_add_child(tree, NULL, F_RULE);
	tmp = ft_ptree_get_node_with_id(tree, id);
	if (test_current_token(tokens_list_struct, VAR_TYPE, tmp))
	{
		return (TRUE);
	}
	(*tokens_list_struct)->index = save_index;
	ft_ptree_remove_node_with_id(tree, id);
	return (FALSE);
}
