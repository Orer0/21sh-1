/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 16:39:01 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/22 03:06:26 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
**	Detecte si on ne pas peut pas terminer sur cette etat
*/

static int	if_take_the_last(int state)
{
	if (state == NUMBER_STATE
		|| state == CHAR_STATE
		|| state == END_D_QUOTE_STATE
		|| state == END_S_QUOTE_STATE
		|| state == S_QUOTE_STATE
		|| state == D_QUOTE_STATE
		|| state == DOLLAR_STATE
		|| state == TILDE_STATE)
		return (TRUE);
	return (FALSE);
}

/*
**	Detecte si l'etat est etoile ou pas
*/

static int is_star(int state)
{
	if (state == STAR_STATE)
		return (TRUE);
	return (FALSE);
}

int		add_new_token(char stack[STACK_SIZE], int n_state, int c_state)
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
			return (FALSE);
		if (data->tokens_list == NULL)
			data->tokens_list = token;
		else
			ft_lstaddend(&(data->tokens_list), token);
	}
	return (TRUE);
}

static int		dollar_case(char (*stack)[STACK_SIZE], int n_state, t_line *line)
{
	char	*dollar;

	if (!is_acceptor(
			automaton_transition(
				n_state, get_index_from_char(line))
			) && line->line[line->i + 1]
		)
		*stack[ft_strlen(*stack) - 1] = 0;
	dollar = get_dollar(line, n_state);
	put_str_in_stack(stack, dollar);
	ft_strdel(&dollar);
	return (TRUE);
}

static int	acceptor_case(char (*stack)[STACK_SIZE], t_line *line, int n_state,
				int c_state)
{
	if (is_star(n_state))
	{
		(*stack)[ft_strlen(*stack) - 1] = 0;
		(line->i)--;
	}
	if (!add_new_token(*stack, n_state, c_state))
		return (FALSE);
	ft_strclr(*stack);
	return (TRUE);
}

/*
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
*/

int	automaton_transition(int x, int y)
{
	static int automaton[HEIGHT][WIDTH] = {
		{CHAR_STATE, NUMBER_STATE, START_STATE, CHAR_STATE, BACKSLASH_STATE, TILDE_STATE, DOLLAR_STATE, DOTCOMMA_V_STATE, PIPE_V_STATE, D_QUOTE_STATE, S_QUOTE_STATE, LEFT_REDIRECTION_STATE, RIGHT_REDIRECTION_STATE, CHAR_STATE, NONE_STATE},
		{CHAR_STATE, CHAR_STATE, STAR_STATE, CHAR_STATE, BACKSLASH_STATE, CHAR_STATE, DOLLAR_STATE, STAR_STATE, STAR_STATE, D_QUOTE_STATE, S_QUOTE_STATE, STAR_STATE, STAR_STATE, CHAR_STATE, NONE_STATE},
		{CHAR_STATE, NUMBER_STATE, STAR_STATE, CHAR_STATE, BACKSLASH_STATE, CHAR_STATE, DOLLAR_STATE, STAR_STATE, STAR_STATE, D_QUOTE_STATE, S_QUOTE_STATE, LEFT_REDIRECTION_STATE, RIGHT_REDIRECTION_STATE, CHAR_STATE, NONE_STATE},
		{CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, NONE_STATE},
		{CHAR_STATE, CHAR_STATE, STAR_STATE, CHAR_STATE, BACKSLASH_STATE, CHAR_STATE, DOLLAR_STATE, STAR_STATE, STAR_STATE, D_QUOTE_STATE, S_QUOTE_STATE, STAR_STATE, STAR_STATE, CHAR_STATE, NONE_STATE},
		{CHAR_STATE, CHAR_STATE, STAR_STATE, CHAR_STATE, BACKSLASH_STATE, CHAR_STATE, DOLLAR_STATE, STAR_STATE, STAR_STATE, D_QUOTE_STATE, S_QUOTE_STATE, STAR_STATE, STAR_STATE, CHAR_STATE, NONE_STATE},
		{D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, BACKSLASH_D_QUOTE_STATE, D_QUOTE_STATE, DOLLAR_STATE, D_QUOTE_STATE, D_QUOTE_STATE, END_D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, NONE_STATE},
		{S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, END_S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, NONE_STATE},
		{CHAR_STATE, NUMBER_STATE, STAR_STATE, CHAR_STATE, BACKSLASH_STATE, CHAR_STATE, DOLLAR_STATE, STAR_STATE, STAR_STATE, D_QUOTE_STATE, S_QUOTE_STATE, STAR_STATE, STAR_STATE, CHAR_STATE, NONE_STATE},
		{CHAR_STATE, NUMBER_STATE, STAR_STATE, CHAR_STATE, BACKSLASH_STATE, CHAR_STATE, DOLLAR_STATE, STAR_STATE, STAR_STATE, D_QUOTE_STATE, S_QUOTE_STATE, STAR_STATE, STAR_STATE, CHAR_STATE, NONE_STATE},
		{D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, NONE_STATE},
		{STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, NONE_STATE, NONE_STATE, STAR_STATE, STAR_STATE, DOUBLE_LEFT_REDIRECTION_STATE, NONE_STATE, LEFT_AGGREGATION_V_STATE, NONE_STATE},
		{STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, NONE_STATE, NONE_STATE, STAR_STATE, STAR_STATE, NONE_STATE, DOUBLE_RIGHT_REDIRECTION_STATE, RIGHT_AGGREGATION_V_STATE, NONE_STATE},
		{STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, NONE_STATE, NONE_STATE, STAR_STATE, STAR_STATE, NONE_STATE, NONE_STATE, NONE_STATE, NONE_STATE},
		{STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, NONE_STATE, NONE_STATE, STAR_STATE, STAR_STATE, NONE_STATE, NONE_STATE, NONE_STATE, NONE_STATE}
	};

	return (automaton[x][y]);
}

int	routine_next_state(char (*stack)[STACK_SIZE], int current_state, int next_state, t_line *line)
{
	if (!is_ignored(current_state, next_state))
		put_char_in_stack(stack, line->line[line->i]);
	if (next_state == NONE_STATE)
	{
		ft_printf(
			"Syntax error near character %c at position %d\n",
			line->line[line->i], line->i + 1
		);
		quit_shell(EXIT_FAILURE, 0);
	}
	else if (next_state == DOLLAR_STATE)
	{
		if (!(dollar_case(stack, next_state, line)))
			return (FALSE);
		return (next_state);
	}
	else if (is_acceptor(next_state))
	{
		if (!acceptor_case(stack, line, next_state, current_state))
			return (FALSE);
		return (START_STATE);
	}
	return (next_state);
}

int	constructor_line_struct(char *str, t_line **line)
{
	if (!(*line = ft_memalloc(sizeof(t_line))))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	(*line)->line = str;
	(*line)->i = -1;
	return (TRUE);
}

/*
**	The main function of the Lexer
*/

int lexer(char *line)
{
	char stack[STACK_SIZE];
	t_line	*line_s;
	int current_state;
	int next_state;

	constructor_line_struct(line, &line_s);
	current_state = START_STATE;
	ft_bzero((void *)&stack, STACK_SIZE);
	while (line_s->line[++(line_s->i)])
	{
		next_state = automaton_transition(
						current_state, get_index_from_char(line_s)
					);
		current_state = routine_next_state(
							&stack, current_state, next_state, line_s
						);
	}
	if (if_take_the_last(current_state))
		if (!add_new_token(stack, next_state, current_state))
			return (FALSE);
	ft_memdel((void **)&line_s);
	return (TRUE);
}
