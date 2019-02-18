/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedures.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 06:13:05 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/18 22:04:59 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/*
**	Command procedure
*/

static void		cmd_procedure(t_ptree **tree)
{
	void	*data;

	if (!(data = ft_memalloc(sizeof((*tree)->data))))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	ft_memcpy(data, (*tree)->data, sizeof((*tree)->data));
	(*tree)->ast = ft_btree_create_node(data);
}

/*
**	Operator procedure
*/

static void		operator_procedure(t_ptree **tree)
{
	(*tree)->ast = NULL;
}

/*
**	Rules procedure
*/

static void		rules_procedure(t_ptree **tree)
{
	void		*data;
	t_list		*tmp;

	tmp = (*tree)->childs_lst;
	if ((*tree)->nb_childs == 3)
	{
		data = ft_memalloc(
				sizeof((*((t_ptree **)(tmp->next->content)))->data));
		if (!data)
			quit_shell(EXIT_FAILURE, MALLOC_ERR);
		ft_memcpy(data, (*((t_ptree **)(tmp->next->content)))->data,
			sizeof((*((t_ptree **)(tmp->next->content)))->data));
		(*tree)->ast = ft_btree_create_node(data);
		(*tree)->ast->left = (*((t_ptree **)(tmp->content)))->ast;
		(*tree)->ast->left->parent = (*tree)->ast;
		(*tree)->ast->right = (*((t_ptree **)(tmp->next->next->content)))->ast;
		(*tree)->ast->right->parent = (*tree)->ast;
	}
	else
		(*tree)->ast = (*((t_ptree **)(tmp->content)))->ast;
}

/*
**	Execute the good procedure
*/

void			execute_post_order_procedure(t_ptree **tree)
{
	if ((*tree)->type == CMD_TYPE || (*tree)->type == VAR_TYPE
		|| (*tree)->type == REDIRECTION_ARG_TYPE
		|| (*tree)->type == AGGREGATION_ARG_TYPE)
		cmd_procedure(tree);
	else if ((*tree)->type == DOTCOMMA_TYPE || (*tree)->type == PIPE_TYPE
		|| (*tree)->type == REDIRECTION_TYPE
		|| (*tree)->type == AND_TYPE
		|| (*tree)->type == OR_TYPE
		|| (*tree)->type == AGGREGATION_TYPE)
		operator_procedure(tree);
	else if ((*tree)->type == S_RULE || (*tree)->type == T_RULE
		|| (*tree)->type == START_TYPE || (*tree)->type == U_RULE
		|| (*tree)->type == V_RULE || (*tree)->type == F_RULE
		|| (*tree)->type == A_RULE || (*tree)->type == B_RULE
		|| (*tree)->type == C_RULE)
		rules_procedure(tree);
}
