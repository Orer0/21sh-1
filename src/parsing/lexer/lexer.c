/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 16:39:01 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/15 23:14:15 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
**	routine_next_state
**	The function will be called by the loop_routine for evaluate the next state
**
**	params: state -> a structure t_state, with the current and the next state
**			line -> the line structure
**			expansion -> the expansion flag
**			stack -> the stack of the automaton
**
**	return: The new current state
**
**	Description:
**
**	- If the state is not an ignored state
**		- Push the current line char in the stack and check the return of the
**		put_char_in_stack function return
**	- If the state is NONE_STATE
**		- Print a syntax error
**	- Else if the state is an expansion
**		- Set the expansion flag to TRUE for this token
**	- Else if the state is acceptor
**		- Call acceptor_case for create a token with the stack content and put
**		the state to START_STATE for continue the state machine from zero
**	- Return the next state
*/

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

/*
**	reopen
**	The function will be called by the loop_routine when the command line is not
**	finished
**
**	params: line_s -> the line structure
**
**	Description:
**
**	- Reopen the prompt and get the next of the line if it's possible. If the
**	data->term is null, it will be not possible to call get_line (using the
**	termcaps library)
*/

static int		reopen(t_line **line_s)
{
	char			*new_line;
	char			*tmp;
	t_shell_data	*data;

	data = shell_data_singleton();
	if (!data->term)
	{
		ft_printf("21sh: syntax error: unexpected end of file\n");
		quit_shell(EXIT_FAILURE, 0);
	}
	if (!(new_line = get_line(PROMPT_MIN, NULL)))
	{
		ft_fd_printf(2
			, "21sh: unexpected EOF while looking for matching '\"'\n");
		return (FALSE);
	}
	if (ft_strequ(new_line, "\n") && data->ctrl_c)
	{
		ft_strdel(&new_line);
		return (FALSE);
	}
	tmp = (*line_s)->line;
	(*line_s)->line = ft_strjoin(tmp, "\n");
	ft_strdel(&tmp);
	tmp = (*line_s)->line;
	(*line_s)->line = ft_strjoin(tmp, new_line);
	ft_strdel(&new_line);
	ft_strdel(&tmp);
	return (TRUE);
}

/*
**	loop_routine
**	The function will be called by the lexer on each character in a loop
**
**	params: state -> a structure t_state, with the current and the next state
**			line_s -> the line structure
**			expansion -> the expansion flag
**			stack -> the stack of the automaton
**	return: FALSE if failed or TRUE
**
**	Description:
**
**	- Get the next state with the array of the automaton transitions in
**	automaton_transition function
**	- Call the routine_next_state with the new next state
**	- If the current state is NONE_STATE, return an error
**	- If the line string is finished but the command is not finished (quote not
**	closed)
**		- Call the function reopen for reopen the prompt and get the next of the
**		command
*/

static int		loop_routine(t_state *state, t_line **line_s, int *expansion
	, char (*stack)[STACK])
{
	(*state).next = automaton_transition((*state).current
		, get_index_from_char(*line_s));
	(*state).current = routine_next_state(stack, state, *line_s, expansion);
	if ((*state).current == NONE_STATE)
		return (FALSE);
	if (!(*line_s)->line[(*line_s)->i + 1] && ((*state).current == D_QUOTE_STATE
		|| (*state).current == S_QUOTE_STATE))
	{
		if (!reopen(line_s))
			return (FALSE);
	}
	return (TRUE);
}

/*
**	The lexer
**	Using a stack automaton with state machine for build the tokens list
**
**	params: line -> The address of the line, representing the complete command
**	return: FALSE if failed or TRUE
**
**	Description:
**
**	- Put the line in a t_line struct (contain the line and the index of the
**	current char position)
**	- Put the current state to START_STATE for starting the automaton
**	- Set the expansion flag to FALSE for the starting
**	- Loop on each character and calling the loop_routine function
**	- Take the last token if the state is good
**	- Put in the line argument the new line (modified by the loop_routine)
**	- Free the t_line structure
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
		{
			*line = line_s->line;
			ft_memdel((void **)&line_s);
			return (FALSE);
		}
	}
	*line = line_s->line;
	if (if_take_the_last(s_state.current))
		add_new_token(stack, &s_state, expansion);
	ft_memdel((void **)&line_s);
	return (TRUE);
}
