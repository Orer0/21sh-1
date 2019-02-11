/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 03:31:29 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/11 01:06:21 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "st.h"
#include "ast.h"

/*
**	Prends une ligne et genere l'ast pour remplir la structure shell_data
*/

int		shell_parser(char **line)
{
	int i;
	t_shell_data *data;

	data = shell_data_singleton();
	i = -1;
	while (ft_isspace((*line)[++i]));
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
