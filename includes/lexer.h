/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 16:38:10 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/28 07:10:11 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "21sh.h"
# include <pwd.h>

# define STACK_SIZE 4096

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

void		unexpected_token_error(char *token);

int 			lexer(char *line);
void 			first_check_tokens_list(t_list *lst);
void 			build_command_token(void);
void 			delete_list_tokens(t_list **lst);
int				replace_tilde(char **str);
void			put_str_in_stack(char (*stack)[STACK_SIZE], char *str);
void			put_char_in_stack(char (*stack)[STACK_SIZE], char c);
int				is_acceptor(int state);
int				is_ignored(int current, int state);
int				get_index_from_char(t_line *line);
char			*get_dollar(t_line *line);
void 			free_token(void *content, size_t size);
int				get_type_of_token(int next_state, int last_state);
void 			token_constructor(char *token, int type, t_token **t);
int				automaton_transition(int x, int y);

#endif
