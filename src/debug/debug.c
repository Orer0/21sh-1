/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 18:28:09 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/18 18:29:34 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "lexer.h"

// static char		*get_str_type(int type)
// {
// 	if (type == NUMBER_TYPE)
// 		return ("NUMBER");
// 	else if (type == OPEN_BRACKET_TYPE)
// 		return ("(");
// 	else if (type == CLOSE_BRACKET_TYPE)
// 		return (")");
// 	else if (type == PLUS_TYPE)
// 		return ("+");
// 	else if (type == MINUS_TYPE)
// 		return ("-");
// 	else if (type == MULTIPLY_TYPE)
// 		return ("x");
// 	else if (type == DIVISION_TYPE)
// 		return ("/");
// 	else if (type == NONE_TYPE)
// 		return ("none");
// 	else if (type == S_RULE)
// 		return ("S_rule");
// 	else if (type == S_PRIME_RULE)
// 		return ("S_prime_rule");
// 	else if (type == T_RULE)
// 		return ("T_rule");
// 	else if (type == T_PRIME_RULE)
// 		return ("T_prime_rule");
// 	else if (type == U_RULE)
// 		return ("U_rule");
// 	else if (type == V_RULE)
// 		return ("V_rule");
// 	else if (type == START_TYPE)
// 		return ("START");
// 	else if (type == END_TYPE)
// 		return ("END");
// 	return ("bad type");
// }

/*
** Print la liste des tokens pour debug
*/

void 	ft_print_tokens(t_list *tokens_list)
{
	t_list		*tmp;

	tmp = tokens_list;
	while (tmp)
	{
		// ft_printf("token = %s, type = %s\n", (*((t_token **)(tmp->content)))->token, get_str_type((*((t_token **)(tmp->content)))->type));
		ft_printf("token = %s\n", (*((t_token **)(tmp->content)))->token);
		tmp = tmp->next;
	}
}
//
// /*
// **	Print la marge en fonction du level
// */
//
// static void 		print_margin(int level)
// {
// 	int i = -1;
// 	while (++i < level)
// 		ft_printf("\t");
// }
//
// /*
// **	Print l'arbre de parsing pour debug
// */
//
// static void 		print_p_tree_rec(int level, t_ptree **tree)
// {
// 	t_list *tmp;
//
// 	if (!tree)
// 		return ;
// 	print_margin(level);
// 	ft_printf("id: %d, type: %s data: %s", (*tree)->id, get_str_type((*tree)->type), (*tree)->data);
// 	tmp = (*tree)->childs_lst;
// 	while (tmp)
// 	{
// 		ft_printf("\n");
// 		print_p_tree_rec(level + 1, ((t_ptree **)(tmp->content)));
// 		tmp = tmp->next;
// 	}
// }
//
// void 		ft_print_parsing_tree(int level, t_ptree **tree)
// {
// 	if (tree && *tree)
// 		print_p_tree_rec(level, tree);
// }
//
// static void		p_ast(void *tree)
// {
// 	ft_printf("type = %s, data = %s\n", get_str_type(((t_ast_token *)(((t_btree *)(tree))->data))->type), ((t_ast_token *)(((t_btree *)(tree))->data))->data);
// }
//
//
// void 		ft_print_ast(t_btree *ast)
// {
// 	ft_btree_apply_prefix(ast, p_ast);
// }
