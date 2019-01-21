/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 18:28:09 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/20 04:46:33 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "lexer.h"

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
	else if (type == COMMAND_TYPE)
		return ("COMMAND");
	else
		return ("NONE_TYPE");
	return ("bad type");
}

/*
** Print la liste des tokens pour debug
*/

void 	ft_print_tokens(t_list *tokens_list)
{
	t_list		*tmp;
	int			i;

	tmp = tokens_list;
	while (tmp)
	{
		ft_printf("token = %s, type = %s\n", (*((t_token **)(tmp->content)))->token, get_str_type((*((t_token **)(tmp->content)))->type));
		if ((*((t_token **)(tmp->content)))->type == COMMAND_TYPE)
		{
			i = -1;
			while (((*((t_token **)(tmp->content)))->tab)[++i])
				ft_printf("\t\t content tab = %s\n", (*((t_token **)(tmp->content)))->tab[i]);
		}
		// ft_printf("token = %s, type = \n", (*((t_token **)(tmp->content)))->token, (*((t_token **)(tmp->content)))->type);
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
