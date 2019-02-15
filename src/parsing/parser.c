/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 03:31:29 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/15 05:25:37 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "st.h"
#include "ast.h"

/*
**	The main parsing function
**
**	params: line -> The address of the line, representing the complete command
**	return: FALSE if failed or TRUE
**
**	Description:
**
**	- Check if the line is valid and not just spaces or tabs
**	- Call the lexer with the line and receive in the data structure the chained
**	list of the tokens
**	- Call the first_check_tokens_list, for rebuild the tokens with the good
**	types and group the variables
**	- Call the build_command_token, for regroup the commands tokens
**	- Call the syntax_tree for build the first syntax tree representing the
**	grammar
**	- Generate the final AST with get_ast
**	- Remove the first syntax tree
**	- Free the line argument
**
**	The AST was built and is ready for the execution
*/

int		shell_parser(char **line)
{
	int				i;
	t_shell_data	*data;
	int				status;

	data = shell_data_singleton();
	i = -1;
	status = 0;
	while (ft_isspace((*line)[++i]))
		;
	if (!(*line)[i])
	{
		ft_strdel(line);
		return (FALSE);
	}
	if (!lexer(line) || !data->tokens_list
		|| !first_check_tokens_list(data->tokens_list))
	{
		ft_strdel(line);
		return (FALSE);
	}
	build_command_token();
	syntax_tree(&data->tokens_list, &data->parse_tree);
	data->ast = get_ast(&data->parse_tree);
	delete_parsing_tree(&data->parse_tree);
	ft_strdel(line);
	return (TRUE);
}
