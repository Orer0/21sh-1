/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 03:31:29 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/21 03:36:04 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		shell_parser(char *line)
{
	t_list		*tokens_list;

	ft_printf("chaine recu : %s\n", line);
	lexer(line, &tokens_list);
	if (!first_check_tokens_list(tokens_list))
	{
		delete_list_tokens(&tokens_list);
		exit(0);
	}
	if (!build_command_token(tokens_list))
	{
		delete_list_tokens(&tokens_list);
		exit(0);
	}
	ft_print_tokens(tokens_list);
	delete_list_tokens(&tokens_list);
	return (TRUE);
}
