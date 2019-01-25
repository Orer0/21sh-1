/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 21:38:35 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/25 00:17:51 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char		*get_env_var(char *name)
{
	char	*var;

	var = getenv(name);
	if (var)
		var = ft_strdup(var);
	else
		var = ft_strdup("");
	if (!var)
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	return (var);
}

char	*get_dollar(t_line *line)
{
	int		next_state;
	char	stack[STACK_SIZE];
	int		state;

	state = DOLLAR_STATE;
	ft_bzero((void *)&stack, STACK_SIZE);
	while (line->line[++(line->i)])
	{
		next_state = automaton_transition(state, get_index_from_char(line));
		if (is_acceptor(next_state))
		{
			(line->i)--;
			return (get_env_var(stack));
		}
		else
		{
			if (!is_ignored(state, next_state))
				put_char_in_stack(&stack, line->line[line->i]);
		}
		state = next_state;
	}
	(line->i)--;
	return (get_env_var(stack));
}
