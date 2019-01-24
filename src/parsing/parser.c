/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 03:31:29 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/24 02:48:00 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "st.h"
#include "ast.h"


/*
**	DEBUG functions
*/

	void 		ft_print_tokens();
	void 		ft_print_parsing_tree(int level, t_ptree **tree);
	void 		ft_print_ast(t_btree *ast);

/*
**	Fin DEBUG
*/

int		shell_parser(char *line)
{
	t_shell_data *data;
	t_ptree		*tree_s;
	t_btree		*ast;

	data = shell_data_singleton();
	// Print chaine recu
	ft_printf("chaine recu : %s\n", line);
	// Lexer call
	lexer(line);
	// first check
	first_check_tokens_list(data->tokens_list);

	// rassembler les commandes
	build_command_token();
	// Print la liste des tokens
	ft_print_tokens();

	// Arbre de syntaxe
	syntax_tree(&(data->tokens_list), &tree_s);
	// Print arbre de syntaxe
	ft_print_parsing_tree(0, &tree_s);

	// AST
	ast = get_ast(&tree_s);
	// Print AST
	ft_printf("\n\n");
	ft_print_ast(ast);

	// Delete all
	delete_parsing_tree(&tree_s);
	delete_ast(ast);


	return (TRUE);
}
