/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 18:28:09 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/25 03:55:14 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "lexer.h"
#include "st.h"
#include "ast.h"

static char		*get_str_type(int type)
{
	if (type == NUMBER_TYPE)
		return ("NUMBER");
	else if (type == WORD_TYPE)
		return ("WORD");
	else if (type == PIPE_TYPE)
		return ("PIPE");
	else if (type == DOTCOMMA_TYPE)
		return ("DOTCOMMA");
	else if (type == REDIRECTION_TYPE)
		return ("REDIRECTION");
	else if (type == AGGREGATION_TYPE)
		return ("AGGREGATION");
	else if (type == TILDE_TYPE)
		return ("TILDE");
	else if (type == D_QUOTE_TYPE)
		return ("D QUOTE");
	else if (type == S_QUOTE_TYPE)
		return ("S QUOTE");
	else if (type == REDIRECTION_ARG_TYPE)
		return ("REDIRECTION ARG");
	else if (type == AGGREGATION_ARG_TYPE)
		return ("AGGREGATION ARG");
	else if (type == IN_RDIR_TYPE)
		return ("IN_RDIR_TYPE");
	else if (type == OUT_RDIR_TYPE)
		return ("OUT_RDIR_TYPE");
	else if (type == OUT_ARDIR_TYPE)
		return ("OUT_ARDIR_TYPE");
	else if (type == HEREDOC_TYPE)
		return ("HEREDOC_TYPE");
	else if (type == DUP_IN_FD_TYPE)
		return ("DUP_IN_FD_TYPE");
	else if (type == DUP_OUT_FD_TYPE)
		return ("DUP_OUT_FD_TYPE");
	else if (type == CMD_TYPE)
		return ("COMMAND");
	else if (type == S_RULE)
		return ("S RULE");
	else if (type == T_RULE)
		return ("T RULE");
	else if (type == U_RULE)
		return ("U RULE");
	else if (type == V_RULE)
		return ("V RULE");
	else if (type == F_RULE)
		return ("F RULE");
	else if (type == A_RULE)
		return ("A RULE");
	else if (type == AND_TYPE)
		return ("AND TYPE");
	else if (type == OR_TYPE)
		return ("OR TYPE");
	else if (type == VAR_TYPE)
		return ("VAR TYPE");
	else if (type == START_TYPE)
		return ("START");
	else
		return ("NONE_TYPE");
	return ("bad type");
}

/*
** Print la liste des tokens pour debug
*/

void 	ft_print_tokens()
{
	t_list		*tmp;
	int			i;
	t_shell_data *data;
	t_list		*tmp3;
	t_var_token *tmpvar;

	data = shell_data_singleton();
	tmp = data->tokens_list;
	while (tmp)
	{
		// if (tmp->prev)
		// 	ft_printf("prev = %s, ", (*((t_token **)(tmp->prev->content)))->token);
		ft_printf("token = %s, type = %s, is expansion [%d]\n", (*((t_token **)(tmp->content)))->token, get_str_type((*((t_token **)(tmp->content)))->type), (*((t_token **)(tmp->content)))->is_expansion);
		if ((*((t_token **)(tmp->content)))->type == VAR_TYPE)
		{
			ft_printf("\t\t value = %s\n", (*((t_var_token **)(tmp->content)))->value);
			tmpvar = (*((t_var_token **)(tmp->content)))->next;
			while (tmpvar)
			{
				ft_printf("\t\t suivante = name: %s, value: %s\n", tmpvar->token, tmpvar->value);
				tmpvar = tmpvar->next;
			}
		}
		else if ((*((t_token **)(tmp->content)))->type == CMD_TYPE)
		{
			i = -1;
			if (get_type_token(tmp) == CMD_TYPE)
			{
				// while (((*((t_cmd_token **)(tmp->content)))->tab)[++i])
				tmp3 = (*((t_cmd_token **)(tmp->content)))->args;
				while (tmp3)
				{
					ft_printf("\t\t ARG! token = %s, type = %s, is expansion [%d]\n", (*((t_cmd_token **)(tmp3->content)))->token, get_str_type((*((t_cmd_token **)(tmp3->content)))->type), (*((t_cmd_token **)(tmp3->content)))->is_expansion);
					tmp3 = tmp3->next;
				}
			}
			if ((*((t_cmd_token **)(tmp->content)))->variables)
			{
				tmpvar = (*((t_var_token **)(tmp->content)))->next;
				while (tmpvar)
				{
					ft_printf("\t\t variable = name: %s, value: %s\n", tmpvar->token, tmpvar->value);
					tmpvar = tmpvar->next;
				}
			}
		}
		// ft_printf("token = %s, type = \n", (*((t_token **)(tmp->content)))->token, (*((t_token **)(tmp->content)))->type);
		tmp = tmp->next;
	}
}

/*
**	Print la marge en fonction du level
*/

static void 		print_margin(int level)
{
	int i = -1;
	while (++i < level)
		ft_printf("\t");
}

/*
**	Print l'arbre de parsing pour debug
*/

static void 		print_p_tree_rec(int level, t_ptree **tree)
{
	t_list *tmp;

	if (!tree)
		return ;
	print_margin(level);
	ft_printf("id: %d, type: %s data: %s", (*tree)->id, get_str_type((*tree)->type), (*tree)->data);
	tmp = (*tree)->childs_lst;
	while (tmp)
	{
		ft_printf("\n");
		print_p_tree_rec(level + 1, ((t_ptree **)(tmp->content)));
		tmp = tmp->next;
	}
}

void 		ft_print_parsing_tree(int level, t_ptree **tree)
{
	if (tree && *tree)
		print_p_tree_rec(level, tree);
}

// static void		p_ast(void *tree)
// {
// 	ft_printf("type = %s, data = %s\n", get_str_type(((t_ast_token *)(((t_btree *)(tree))->data))->type), ((t_ast_token *)(((t_btree *)(tree))->data))->data);
// 	if (((t_btree *)(tree))->left)
// 		ft_printf("->left : %s\n", ((t_ast_token *)(((t_btree *)(tree))->left->data))->data);
// 	if (((t_btree *)(tree))->right)
// 		ft_printf("->right : %s\n", ((t_ast_token *)(((t_btree *)(tree))->right->data))->data);
// }

/*
**	Print l'arbre de parsing pour debug
*/

static void 		print_ast_rec(int level, t_btree *tree)
{
	if (!tree)
		return ;
	print_margin(level);
	ft_printf("type: %s data: %s", get_str_type(((t_ast_token *)(tree->data))->type), ((t_ast_token *)(tree->data))->data);
	if (tree->left)
	{
		ft_printf("\n");
		print_ast_rec(level + 1, tree->left);
	}
	if (tree->right)
	{
		ft_printf("\n");
		print_ast_rec(level + 1, tree->right);
	}
}

void 		ft_print_ast(t_btree *ast)
{
	if (ast)
		print_ast_rec(0, ast);
	// ft_btree_apply_prefix(ast, p_ast);
}
