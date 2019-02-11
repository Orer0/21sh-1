/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 16:38:10 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/11 00:24:23 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "21sh.h"
# include <pwd.h>

# define STACK 4096

typedef enum 	e_states
{
	START_STATE = 0,
	CHAR_STATE,
	NUMBER_STATE,
	BACKSLASH_STATE,
	TILDE_STATE,
	DOLLAR_STATE,
	EQUAL_STATE,
	PIPE_STATE,
	AMPERSAND_STATE,
	AND_STATE,
	OR_STATE,
	D_QUOTE_STATE,
	S_QUOTE_STATE,
	END_D_QUOTE_STATE,
	END_S_QUOTE_STATE,
	BACKSLASH_D_QUOTE_STATE,
	LEFT_REDIRECTION_STATE,
	RIGHT_REDIRECTION_STATE,
	DOUBLE_LEFT_REDIRECTION_STATE,
	DOUBLE_RIGHT_REDIRECTION_STATE,
	DOTCOMMA_V_STATE,
	SPACE_V_STATE,
	LEFT_REDIRECTION_V_STATE,
	RIGHT_REDIRECTION_V_STATE,
	LEFT_AGGREGATION_V_STATE,
	RIGHT_AGGREGATION_V_STATE,
	STAR_STATE,
	NONE_STATE
}				t_states;

typedef enum 	e_index
{
	CHAR_INDEX = 0,
	NUMBER_INDEX,
	SPACES_INDEX,
	DASH_INDEX,
	BACKSLASH_INDEX,
	EQUAL_INDEX,
	TILDE_INDEX,
	DOLLAR_INDEX,
	DOTCOMMA_INDEX,
	PIPE_INDEX,
	D_QUOTE_INDEX,
	S_QUOTE_INDEX,
	LEFT_REDIRECTION_INDEX,
	RIGHT_REDIRECTION_INDEX,
	AMPERSAND_INDEX,
	NONE_INDEX
}				t_index;

typedef struct	s_line
{
	char		*line;
	int			i;
}				t_line;

int				if_take_the_last(int state);
int 			is_star(int state);
int				acceptor_case(char (*stack)[STACK], t_line *line, int n_state
					, int c_state, int expansion);
void			unexpected_token_error(char *token);
int				first_check_redirections(t_list *lst);
int				first_check_aggregations(t_list *lst);
void			first_check_variables(t_list *lst);
int				return_syntax_error(char *str);
int				first_check_operators(t_list **lst);
int				first_check_heredoc(t_list **lst);
void			put_arg_in_cmd_list(t_list **lst, t_list **args_list);
int 			lexer(char **line);
int				add_new_token(char stack[STACK], int n_state, int c_state, int expansion);
int				constructor_line_struct(char *str, t_line **line);
int 			first_check_tokens_list(t_list *lst);
void 			build_command_token(void);
void 			delete_list_tokens(t_list **lst);
int				put_str_in_stack(char (*stack)[STACK], char *str);
int				put_char_in_stack(char (*stack)[STACK], char c);
int				is_acceptor(int state);
int				is_ignored(int current, int state);
int				get_index_from_char(t_line *line);
void 			free_token(void *content, size_t size);
int				get_type_of_token(int next_state, int last_state);
void 			token_constructor(char *token, int type, t_token **t);
int				automaton_transition(int x, int y);

#endif
