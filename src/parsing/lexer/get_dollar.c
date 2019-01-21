/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 21:38:35 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/21 02:25:10 by ndubouil         ###   ########.fr       */
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
	return (var);
}

char	*get_dollar(char *line, int *i, int state, int A[HEIGHT][WIDTH])
{
	int		next_state;
	char	stack[STACK_SIZE];

	ft_bzero((void *)&stack, STACK_SIZE);
	while (line[++(*i)])
	{
		next_state = A[state][get_index_from_char(line, (*i))];
		if (is_acceptor(next_state))
		{
			(*i)--;
			return (get_env_var(stack));
		}
		else
		{
			if (!is_ignored(state, next_state))
				put_char_in_stack(&stack, line[(*i)]);
		}
		state = next_state;
	}
	(*i)--;
	return (get_env_var(stack));
}
