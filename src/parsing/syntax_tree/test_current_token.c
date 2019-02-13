/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_current_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 05:46:22 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/13 18:55:52 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "st.h"

int		test_current_token(t_tokens_list **tokens_s, int type, t_ptree **tree)
{
	t_list	*good_token;

	good_token = ft_lsti((*tokens_s)->tokens_list, (*tokens_s)->index);
	if ((*tokens_s)->index + 1 > (*tokens_s)->size)
		return (FALSE);
	if (type_cmp((*((t_token **)(good_token->content)))->type, type))
	{
		ft_ptree_add_child(tree, good_token->content,
			(*((t_token **)(good_token->content)))->type);
		(*tokens_s)->index++;
		return (TRUE);
	}
	return (FALSE);
}
