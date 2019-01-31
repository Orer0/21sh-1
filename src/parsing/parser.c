/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 03:31:29 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/31 01:34:18 by ndubouil         ###   ########.fr       */
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

/*
**	Prends une ligne et genere l'ast pour remplir la structure shell_data
*/

int		shell_parser(char *line)
{
	t_shell_data *data;

	data = shell_data_singleton();
	// Print chaine recu
	ft_printf("chaine recu : %s\n", line);
	// Lexer call
	lexer(line);
	ft_printf("\n\n APRES LE LEXER \n\n");
	ft_print_tokens();
	first_check_tokens_list(data->tokens_list);
	ft_printf("\n\n APRES FIRST CHECK \n\n");
	ft_print_tokens();
	build_command_token();
	ft_printf("\n\n APRES BUILD COMMAND \n\n");
	ft_print_tokens();
	// Arbre de syntaxe
	syntax_tree(&data->tokens_list, &data->parse_tree);
	ft_printf("\n\n");
	// Print arbre de syntaxe
	ft_print_parsing_tree(0, &data->parse_tree);
	// AST
	data->ast = get_ast(&data->parse_tree);
	delete_parsing_tree(&data->parse_tree);
	// Print AST
	ft_printf("\n\n");
	ft_print_ast(data->ast);
	ft_printf("\n\n");
	// Delete all
	// delete_ast(&data->ast);

	return (TRUE);
}
