/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedures.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 06:13:05 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/03 04:38:52 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/*
**	Procedure pour un nombre
*/

static void 		cmd_procedure(t_ptree **tree)
{
	void 			*data;

	data = ft_memalloc(sizeof((*tree)->data));
	ft_memcpy(data, (*tree)->data, sizeof((*tree)->data));
	(*tree)->ast = ft_btree_create_node(data);
}

/*
**	Procedure pour un operateur
*/

static void 		operator_procedure(t_ptree **tree)
{
	(*tree)->ast = NULL;
}

/*
**	Procedure pour un noeud A
*/

// static void 		a_procedure(t_ptree **tree)
// {
// 	void 	*data;
// 	t_list			*tmp;
//
// 	tmp = (*tree)->childs_lst;
// 	if ((*tree)->nb_childs == 3)
// 	{
// 		data = ft_memalloc(
// 				sizeof((*((t_ptree **)(tmp->next->content)))->data));
// 		ft_memcpy(data, (*((t_ptree **)(tmp->next->content)))->data,
// 			sizeof((*((t_ptree **)(tmp->next->content)))->data));
// 		(*tree)->ast = ft_btree_create_node(data);
// 		(*tree)->ast->left = (*((t_ptree **)(tmp->next->next->content)))->ast;
// 		(*tree)->ast->left->parent = (*tree)->ast;
// 		(*tree)->ast->right = (*((t_ptree **)(tmp->content)))->ast;
// 		(*tree)->ast->right->parent = (*tree)->ast;
// 	}
// 	else
// 		(*tree)->ast = (*((t_ptree **)(tmp->content)))->ast;
// }

/*
**	Procedure pour un noeud regle
*/

static void 		rules_procedure(t_ptree **tree)
{
	void 	*data;
	t_list			*tmp;

	tmp = (*tree)->childs_lst;
	if ((*tree)->nb_childs == 3)
	{
		data = ft_memalloc(
				sizeof((*((t_ptree **)(tmp->next->content)))->data));
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
**	Execute la bonne procedure en fonction du type du noeud
*/

void 		execute_post_order_procedure(t_ptree **tree)
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
	// else if ((*tree)->type == A_RULE)
	// 	a_procedure(tree);
	else if ((*tree)->type == S_RULE || (*tree)->type == T_RULE
		|| (*tree)->type == START_TYPE || (*tree)->type == U_RULE
		|| (*tree)->type == V_RULE || (*tree)->type == F_RULE || (*tree)->type == A_RULE || (*tree)->type == B_RULE)
		rules_procedure(tree);
}
