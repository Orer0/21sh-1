/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 21:38:35 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/03 01:21:05 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char		*get_env_var(char *name)
{
	t_varenv	*var;
	char	*content;
	t_shell_data	*data;

	data = shell_data_singleton();
	var = get_env_var_by_name(&data->intern_env_lst, name);
	if (var)
		content = ft_strdup(var->content);
	else
		content = ft_strdup("");
	if (!content)
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
	return (content);
}

// char	*get_dollar(char *line)
// {
// 	int		next_state;
// 	char	stack[STACK_SIZE];
// 	int		state;
//
// 	state = DOLLAR_STATE;
// 	ft_bzero((void *)&stack, STACK_SIZE);
// 	while (line->line[++(line->i)])
// 	{
// 		next_state = automaton_transition(state, get_index_from_char(line));
// 		if (is_acceptor(next_state))
// 		{
// 			(line->i)--;
// 			return (get_env_var(stack));
// 		}
// 		else
// 		{
// 			if (!is_ignored(state, next_state))
// 				put_char_in_stack(&stack, line->line[line->i]);
// 		}
// 		state = next_state;
// 	}
// 	(line->i)--;
// 	return (get_env_var(stack));
// }

char	*get_dollar(char *line)
{
	int		i;
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
