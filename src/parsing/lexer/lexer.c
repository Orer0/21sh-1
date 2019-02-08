/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 16:39:01 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/08 22:14:28 by ndubouil         ###   ########.fr       */
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
		|| state == AND_STATE
		|| state == OR_STATE
		|| state == PIPE_STATE
		// || state == DOTCOMMA_V_STATE
		|| state == EQUAL_STATE
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

static int	acceptor_case(char (*stack)[STACK_SIZE], t_line *line, int n_state,
				int c_state, int expansion)
{
	if (is_star(n_state))
	{
		(*stack)[ft_strlen(*stack) - 1] = 0;
		(line->i)--;
	}
	add_new_token(*stack, n_state, c_state, expansion);
	ft_strclr(*stack);
	return (TRUE);
}

int	routine_next_state(char (*stack)[STACK_SIZE], int current_state,
	int next_state, t_line *line, int *expansion)
{
	if (!is_ignored(current_state, next_state))
		put_char_in_stack(stack, line->line[line->i]);
	if (next_state == NONE_STATE)
	{
		ft_fd_printf(
			2, "21sh: syntax error near character %c at position %d\n",
			line->line[line->i], line->i + 1
		);
	}
	else if ((next_state == DOLLAR_STATE || next_state == TILDE_STATE)
		&& current_state != DOLLAR_STATE)
	{
		(*expansion) = TRUE;
		return (next_state);
	}
	else if (is_acceptor(next_state))
	{
		acceptor_case(stack, line, next_state, current_state, *expansion);
		(*expansion) = FALSE;
		return (START_STATE);
	}
	return (next_state);
}

/*
**	The main function of the Lexer
*/

int lexer(char **line)
{
	char stack[STACK_SIZE];
	t_line	*line_s;
	int current_state;
	int next_state;
	int	expansion;
	char *tmp;
	char *newline;
	t_shell_data	*data;

	data = shell_data_singleton();
	constructor_line_struct(*line, &line_s);
	current_state = START_STATE;
	ft_bzero((void *)&stack, STACK_SIZE);
	expansion = FALSE;
	while (line_s->line[++(line_s->i)])
	{
		next_state = automaton_transition(
						current_state, get_index_from_char(line_s));
		current_state = routine_next_state(
						&stack, current_state, next_state, line_s, &expansion);
		if (current_state == NONE_STATE)
		{
			ft_memdel((void **)&line_s);
			return (FALSE);
		}
		if (!line_s->line[line_s->i + 1] && (current_state == D_QUOTE_STATE || current_state == S_QUOTE_STATE))
		{
			tmp = line_s->line;
			if (data->term)
				newline = get_line(PROMPT_MIN);
			else
			{
				ft_printf("21sh: syntax error: unexpected end of file\n");
				quit_shell(EXIT_FAILURE, 0);
			}
			line_s->line = ft_strjoin(tmp, newline);
			ft_strdel(&newline);
			ft_strdel(&tmp);
		}
	}
	*line = line_s->line;
	if (if_take_the_last(current_state))
		add_new_token(stack, next_state, current_state, expansion);
	ft_memdel((void **)&line_s);
	return (TRUE);
}
