/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_shell_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 07:12:43 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/28 07:13:37 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "lexer.h"
#include "st.h"
#include "ast.h"

void 	clean_shell_data(void)
{
	t_shell_data *data;

	data = shell_data_singleton();
	if (data->tokens_list)
		delete_list_tokens(&data->tokens_list);
	if (data->parse_tree)
		delete_parsing_tree(&data->parse_tree);
	if (data->ast)
		delete_ast(&data->ast);
}
