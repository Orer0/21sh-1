/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 18:28:09 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/02 04:05:33 by ndubouil         ###   ########.fr       */
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

void 	print_var_token(t_var_token *token)
{
	t_list		*tmp;

	tmp = get_var_list_token(token);
	while (tmp)
	{
		ft_printf("\t\t variable = token: %s\n", get_token_token(tmp->content));
		tmp = tmp->next;
	}
}

/*
** Print la liste des tokens pour debug
*/

void 	ft_print_tokens()
{
	t_list		*tmp;
	t_list		*tmp2;
	t_shell_data *data;

	data = shell_data_singleton();
	tmp = data->tokens_list;
	// Pour chaque token
	while (tmp)
	{
		ft_printf("token = %s, type = %s, is expansion [%d]\n", get_token_token(tmp->content), get_str_type(get_type_token(tmp->content)), get_expansion_token(tmp->content));
		if (get_type_token(tmp->content) == VAR_TYPE)
			print_var_token(((t_var_token *)(tmp->content)));
		else if ((*((t_token **)(tmp->content)))->type == CMD_TYPE)
		{
			if (get_type_token(tmp->content) == CMD_TYPE)
			{
				tmp2 = get_args_token(tmp->content);
				while (tmp2)
				{
					ft_printf("\t\t ARG! token = %s, type = %s, is expansion [%d]\n", get_token_token(tmp2->content), get_str_type(get_type_token(tmp2->content)), get_expansion_token(tmp2->content));
					tmp2 = tmp2->next;
				}
			}
			if ((*((t_cmd_token **)(tmp->content)))->var_token)
			{
				if (get_var_list_in_cmd_token(tmp->content))
				{
					ft_printf("\t\t variable = token: %s\n", get_token_token((*((t_cmd_token **)(tmp->content)))->var_token));
					tmp2 = get_var_list_in_cmd_token(tmp->content);
					while (tmp2)
					{
						ft_printf("\t\t variable = token: %s\n", get_token_token(tmp2->content));
						tmp2 = tmp2->next;
					}
				}
			}
		}
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
	ft_printf("id: %d, type: %s", (*tree)->id, get_str_type((*tree)->type));
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
	ft_printf("NOEUD -> type: %s token: %s, exp: %d", get_str_type(get_type_token(tree->data)), get_token_token(tree->data), get_expansion_token(tree->data));
	if (get_type_token(tree->data) == VAR_TYPE)
	{
		t_list		*tmp_lst;

		tmp_lst = get_var_list_token(tree->data);
		while (tmp_lst)
		{
			ft_printf("\n");
			print_margin(level);
			ft_printf("\tvariable suivante = token: %s, exp: %d", get_token_token(tmp_lst->content), get_expansion_token(tree->data));
			tmp_lst = tmp_lst->next;
		}
		// print_var_token((*((t_var_token **)(((t_ast_token *)(tree->data))->data))));
	}
	if (get_type_token(tree->data) == CMD_TYPE)
	{
		t_list		*tmp_lst;

		tmp_lst = get_args_token(tree->data);
		while (tmp_lst)
		{
			ft_printf("\n");
			print_margin(level);
			ft_printf("\targ = token: %s, exp: %d", get_token_token(tmp_lst->content), get_expansion_token(tree->data));
			tmp_lst = tmp_lst->next;
		}
		if (get_var_token_in_cmd_token(tree->data))
		{
			ft_printf("\n");
			print_margin(level);
			ft_printf("\tvariable = token: %s, exp: %d", get_var_token_in_cmd_token(tree->data)->token, get_expansion_token(tree->data));
			if (get_var_list_in_cmd_token(tree->data))
			{
				tmp_lst = get_var_list_in_cmd_token(tree->data);
				while (tmp_lst)
				{
					ft_printf("\n");
					print_margin(level);
					ft_printf("\tvariable = token: %s, exp: %d", get_token_token(tmp_lst->content), get_expansion_token(tree->data));
					tmp_lst = tmp_lst->next;
				}
			}
		}
	}
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
}
