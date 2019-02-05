/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 03:31:29 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/05 05:26:12 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"
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

// static int		not_terminal_type(t_list *lst)
// {
// 	int		type;
//
// 	if (!lst)
// 		return (FALSE);
// 	type = get_type_token(lst->content);
// 	if (type == PIPE_TYPE
// 		|| type == D_QUOTE_TYPE
// 		|| type == S_QUOTE_TYPE
// 		|| type == AND_TYPE
// 		|| type == OR_TYPE)
// 		return (TRUE);
// 		// unexpected_token_error(get_token_token(lst->content));
// 	return (FALSE);
// }

/*
**	Prends une ligne et genere l'ast pour remplir la structure shell_data
*/

int		shell_parser(char **line)
{
	int i;
	t_shell_data *data;

	data = shell_data_singleton();
	// Print chaine recu
	ft_printf("chaine recu : %s\n", *line);
	i = -1;
	while (ft_isspace((*line)[++i]));
	if (!(*line)[i])
	{
		ft_strdel(line);
		return (FALSE);
	}
	// Lexer call
	if (!lexer(line))
	{
		ft_strdel(line);
		return (FALSE);
	}
	ft_printf("\n\n APRES LE LEXER \n\n");
	ft_print_tokens();
	if (!data->tokens_list)
	{
		ft_strdel(line);
		return (FALSE);
	}
	if (!first_check_tokens_list(data->tokens_list))
	{
		ft_strdel(line);
		return (FALSE);
	}
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

	// Del la line
	ft_strdel(line);

	// Print AST
	ft_printf("\n\n");
	ft_print_ast(data->ast);
	ft_printf("\n\n");
	// Delete all
	// delete_ast(&data->ast);

	return (TRUE);
}
