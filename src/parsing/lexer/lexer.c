/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 16:39:01 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/12 06:02:44 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int		routine_next_state(char (*stack)[STACK], t_state *state
	, t_line *line, int *expansion)
{
	if (!is_ignored((*state).current, (*state).next))
		if (!put_char_in_stack(stack, line->line[line->i]))
			return (NONE_STATE);
	if ((*state).next == NONE_STATE)
	{
		ft_fd_printf(2, "21sh: syntax error near character %c at position %d\n"
			, line->line[line->i], line->i + 1);
	}
	else if (((*state).next == DOLLAR_STATE || (*state).next == TILDE_STATE)
		&& (*state).current != DOLLAR_STATE)
	{
		(*expansion) = TRUE;
		return ((*state).next);
	}
	else if (is_acceptor((*state).next))
	{
		acceptor_case(stack, line, state, *expansion);
		(*expansion) = FALSE;
		return (START_STATE);
	}
	return ((*state).next);
}

static void		reopen(t_line **line_s)
{
	char			*newline;
	char			*tmp;
	t_shell_data	*data;

	data = shell_data_singleton();
	tmp = (*line_s)->line;
	if (!data->term)
	{
		ft_printf("21sh: syntax error: unexpected end of file\n");
		quit_shell(EXIT_FAILURE, 0);
	}
	newline = get_line(PROMPT_MIN);
	(*line_s)->line = ft_strjoin(tmp, newline);
	ft_strdel(&newline);
	ft_strdel(&tmp);
}

static int		loop_routine(t_state *state, t_line **line_s, int *expansion
	, char (*stack)[STACK])
{
	(*state).next = automaton_transition((*state).current
		, get_index_from_char(*line_s));
	(*state).current = routine_next_state(stack, state, *line_s, expansion);
	if ((*state).current == NONE_STATE)
	{
		ft_memdel((void **)line_s);
		return (FALSE);
	}
	if (!(*line_s)->line[(*line_s)->i + 1] && ((*state).current == D_QUOTE_STATE
		|| (*state).current == S_QUOTE_STATE))
		reopen(line_s);
	return (TRUE);
}

/*
**	The main function of the Lexer
*/

int				lexer(char **line)
{
	char	stack[STACK];
	t_line	*line_s;
	t_state	s_state;
	int		expansion;

	constructor_line_struct(*line, &line_s);
	s_state.current = START_STATE;
	ft_bzero((void *)&stack, STACK);
	expansion = FALSE;
	while (line_s->line[++(line_s->i)])
	{
		if (!loop_routine(&s_state, &line_s, &expansion, &stack))
			return (FALSE);
	}
	*line = line_s->line;
	if (if_take_the_last(s_state.current))
		add_new_token(stack, &s_state, expansion);
	ft_memdel((void **)&line_s);
	return (TRUE);
}
