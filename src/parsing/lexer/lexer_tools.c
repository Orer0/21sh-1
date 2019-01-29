/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 22:58:13 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/28 22:59:08 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	constructor_line_struct(char *str, t_line **line)
{
	if (!(*line = ft_memalloc(sizeof(t_line))))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	(*line)->line = str;
	(*line)->i = -1;
	return (TRUE);
}

int		add_new_token(char stack[STACK_SIZE], int n_state, int c_state, int expansion)
{
	t_list	*token;
	t_token	*token_struct;
	t_shell_data	*data;

	data = shell_data_singleton();
	if (stack[0])
	{
		token_constructor(
			stack, get_type_of_token(n_state, c_state), &token_struct
		);
		if (!(token = ft_lstnew(&token_struct, sizeof(t_token))))
			quit_shell(EXIT_FAILURE, MALLOC_ERR);
		if (expansion)
			set_expansion_token(token->content, expansion);
		if (data->tokens_list == NULL)
			data->tokens_list = token;
		else
			ft_lstaddend(&(data->tokens_list), token);
	}
	return (TRUE);
}
