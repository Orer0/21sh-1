/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_rule.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 05:54:03 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/13 18:56:47 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "st.h"

int		b_prime_rule(t_tokens_list **tokens_list_struct, t_ptree **tree)
{
	int		save_index;

	save_index = (*tokens_list_struct)->index;
	if (test_current_token(tokens_list_struct, REDIRECTION_TYPE, tree)
		&& b_rule(tokens_list_struct, tree)
		&& b_prime_rule(tokens_list_struct, tree))
	{
		return (TRUE);
	}
	(*tokens_list_struct)->index = save_index;
	if (test_current_token(tokens_list_struct, AGGREGATION_TYPE, tree)
		&& c_rule(tokens_list_struct, tree)
		&& c_prime_rule(tokens_list_struct, tree))
	{
		return (TRUE);
	}
	(*tokens_list_struct)->index = save_index;
	return (TRUE);
}

int		b_rule(t_tokens_list **tokens_list_struct, t_ptree **tree)
{
	int			id;
	int			save_index;
	t_ptree		**tmp;

	id = ft_ptree_add_child(tree, NULL, B_RULE);
	tmp = ft_ptree_get_node_with_id(tree, id);
	save_index = (*tokens_list_struct)->index;
	if (test_current_token(tokens_list_struct, REDIRECTION_ARG_TYPE, tmp)
		&& b_prime_rule(tokens_list_struct, tmp))
	{
		return (TRUE);
	}
	(*tokens_list_struct)->index = save_index;
	ft_ptree_remove_node_with_id(tree, id);
	return (FALSE);
}
