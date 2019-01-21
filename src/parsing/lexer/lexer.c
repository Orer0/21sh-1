/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 16:39:01 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/21 03:28:30 by ndubouil         ###   ########.fr       */
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



int		add_new_token(char stack[STACK_SIZE], int n_state, int c_state, t_list **lst)
{
	t_list	*token;
	t_token	*token_struct;

	if (stack[0])
	{
		if (!create_token(stack, n_state, c_state, &token_struct))
			return (FALSE);
		if (!(token = ft_lstnew(&token_struct, sizeof(t_token))))
			return (FALSE);
		if ((*lst) == NULL)
			(*lst) = token;
		else
			ft_lstaddend(lst, token);
	}
	return (TRUE);
}

static int		dollar_case(char (*stack)[STACK_SIZE], int n_state, char *line, int *i, int a[HEIGHT][WIDTH])
{
	char	*dollar;

	if (!is_acceptor(a[n_state][get_index_from_char(line, *i + 1)]) && line[*i + 1])
		*stack[ft_strlen(*stack) - 1] = 0;
	if (!(dollar = get_dollar(line, i, n_state, a)))
		return (FALSE);
	put_str_in_stack(stack, dollar);
	ft_strdel(&dollar);
	return (TRUE);
}

static int	acceptor_case(char (*stack)[STACK_SIZE], int *i, int n_state,
				int c_state, t_list **tokens_list)
{
	if (is_star(n_state))
	{
		(*stack)[ft_strlen(*stack) - 1] = 0;
		(*i)--;
	}
	if (!add_new_token(*stack, n_state, c_state, tokens_list))
		return (FALSE);
	ft_strclr(*stack);
	return (TRUE);
}

// int 	**get_automata(void)
// {
// 	int		**automata;
// 	int		i;
//
// 	automata = ft_memalloc(HEIGHT * sizeof(int *));
// 	i = -1;
// 	while (++i < WIDTH)
// 		automata[i] = ft_memalloc(WIDTH * sizeof(int));
// 	automata[0] = {CHAR_STATE, NUMBER_STATE, START_STATE, CHAR_STATE, BACKSLASH_STATE, TILDE_STATE, DOLLAR_STATE, DOTCOMMA_V_STATE, PIPE_V_STATE, D_QUOTE_STATE, S_QUOTE_STATE, LEFT_REDIRECTION_STATE, RIGHT_REDIRECTION_STATE, CHAR_STATE, NONE_STATE};
// 	automata[1] = {CHAR_STATE, CHAR_STATE, STAR_STATE, CHAR_STATE, BACKSLASH_STATE, CHAR_STATE, DOLLAR_STATE, STAR_STATE, STAR_STATE, D_QUOTE_STATE, S_QUOTE_STATE, STAR_STATE, STAR_STATE, CHAR_STATE, NONE_STATE};
// 	automata[2] = {CHAR_STATE, NUMBER_STATE, STAR_STATE, CHAR_STATE, BACKSLASH_STATE, CHAR_STATE, DOLLAR_STATE, STAR_STATE, STAR_STATE, D_QUOTE_STATE, S_QUOTE_STATE, LEFT_REDIRECTION_STATE, RIGHT_REDIRECTION_STATE, CHAR_STATE, NONE_STATE};
// 	automata[3] = {CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, CHAR_STATE, NONE_STATE};
// 	automata[4] = {CHAR_STATE, CHAR_STATE, STAR_STATE, CHAR_STATE, BACKSLASH_STATE, CHAR_STATE, DOLLAR_STATE, STAR_STATE, STAR_STATE, D_QUOTE_STATE, S_QUOTE_STATE, STAR_STATE, STAR_STATE, CHAR_STATE, NONE_STATE};
// 	automata[5] = {CHAR_STATE, CHAR_STATE, STAR_STATE, CHAR_STATE, BACKSLASH_STATE, CHAR_STATE, DOLLAR_STATE, STAR_STATE, STAR_STATE, D_QUOTE_STATE, S_QUOTE_STATE, STAR_STATE, STAR_STATE, CHAR_STATE, NONE_STATE};
// 	automata[6] = {D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, BACKSLASH_D_QUOTE_STATE, D_QUOTE_STATE, DOLLAR_STATE, D_QUOTE_STATE, D_QUOTE_STATE, END_D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, NONE_STATE};
// 	automata[7] = {S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, END_S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, S_QUOTE_STATE, NONE_STATE};
// 	automata[8] = {CHAR_STATE, NUMBER_STATE, STAR_STATE, CHAR_STATE, BACKSLASH_STATE, CHAR_STATE, DOLLAR_STATE, STAR_STATE, STAR_STATE, D_QUOTE_STATE, S_QUOTE_STATE, STAR_STATE, STAR_STATE, CHAR_STATE, NONE_STATE};
// 	automata[9] = {CHAR_STATE, NUMBER_STATE, STAR_STATE, CHAR_STATE, BACKSLASH_STATE, CHAR_STATE, DOLLAR_STATE, STAR_STATE, STAR_STATE, D_QUOTE_STATE, S_QUOTE_STATE, STAR_STATE, STAR_STATE, CHAR_STATE, NONE_STATE};
// 	automata[10] = {D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, D_QUOTE_STATE, NONE_STATE};
// 	automata[11] = {STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, NONE_STATE, NONE_STATE, STAR_STATE, STAR_STATE, DOUBLE_LEFT_REDIRECTION_STATE, NONE_STATE, LEFT_AGGREGATION_V_STATE, NONE_STATE};
// 	automata[12] = {STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, NONE_STATE, NONE_STATE, STAR_STATE, STAR_STATE, NONE_STATE, DOUBLE_RIGHT_REDIRECTION_STATE, RIGHT_AGGREGATION_V_STATE, NONE_STATE};
// 	automata[13] = {STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, NONE_STATE, NONE_STATE, STAR_STATE, STAR_STATE, NONE_STATE, NONE_STATE, NONE_STATE, NONE_STATE};
// 	automata[14] = {STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, STAR_STATE, NONE_STATE, NONE_STATE, STAR_STATE, STAR_STATE, NONE_STATE, NONE_STATE, NONE_STATE, NONE_STATE};
// 	return (automata);
// }

/*
**	The main function of the Lexer
*/

int lexer(char *line, t_list **tokens_list)
{
	static int A[HEIGHT][WIDTH] = {
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
	char stack[STACK_SIZE];
	int current_state;
	int next_state;
	int i;

	current_state = START_STATE;
	ft_bzero((void *)&stack, STACK_SIZE);
	i = -1;
	while (line[++i])
	{
		next_state = A[current_state][get_index_from_char(line, i)];
		if (!is_ignored(current_state, next_state))
			put_char_in_stack(&stack, line[i]);
		if (next_state == NONE_STATE)
		{
			ft_printf("Syntax error near character %c at position %d\n", line[i], i + 1);
			delete_list_tokens(tokens_list);
			exit(0);
		}
		else if (next_state == DOLLAR_STATE)
		{
			if (!(dollar_case(&stack, next_state, line, &i, A)))
				return (FALSE);
		}
		else if (is_acceptor(next_state))
		{
			if (!acceptor_case(&stack, &i, next_state, current_state, tokens_list))
				return (FALSE);
			current_state = START_STATE;
			continue;
		}
		current_state = next_state;
	}
	if (if_take_the_last(current_state))
		if (!add_new_token(stack, next_state, current_state, tokens_list))
			return (FALSE);
	return (TRUE);
}
