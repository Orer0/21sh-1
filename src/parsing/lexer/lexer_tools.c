/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 22:58:13 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/13 06:36:30 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		constructor_line_struct(char *str, t_line **line)
{
	if (!(*line = ft_memalloc(sizeof(t_line))))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	(*line)->line = str;
	(*line)->i = -1;
	return (TRUE);
}

int		add_new_token(char stack[STACK], t_state *state, int expan)
{
	t_list			*token;
	t_token			*token_struct;
	t_shell_data	*data;

	data = shell_data_singleton();
	if (stack[0])
	{
		token_constructor(stack, get_type_of_token((*state).next
			, (*state).current), &token_struct);
		if (!(token = ft_lstnew(&token_struct, sizeof(t_token))))
			quit_shell(EXIT_FAILURE, MALLOC_ERR);
		if (expan)
			set_expansion_token(token->content, expan);
		if (data->tokens_list == NULL)
			data->tokens_list = token;
		else
			ft_lstaddend(&(data->tokens_list), token);
	}
	return (TRUE);
}

int		if_take_the_last(int state)
{
	if (state == NUMBER_STATE
		|| state == CHAR_STATE
		|| state == END_D_QUOTE_STATE
		|| state == END_S_QUOTE_STATE
		|| state == S_QUOTE_STATE
		|| state == D_QUOTE_STATE
		|| state == DOLLAR_STATE
		|| state == AND_STATE
		|| state == OR_STATE
		|| state == PIPE_STATE
		|| state == EQUAL_STATE
		|| state == TILDE_STATE)
		return (TRUE);
	return (FALSE);
}

int		is_star(int state)
{
	if (state == STAR_STATE)
		return (TRUE);
	return (FALSE);
}

int		acceptor_case(char (*stack)[STACK], t_line *line, t_state *state
	, int expansion)
{
	if (is_star((*state).next))
	{
		(*stack)[ft_strlen(*stack) - 1] = 0;
		(line->i)--;
	}
	add_new_token(*stack, state, expansion);
	ft_strclr(*stack);
	return (TRUE);
}
