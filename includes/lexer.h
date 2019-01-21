/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 16:38:10 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/21 03:35:56 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "21sh.h"
# include <pwd.h>

# define HEIGHT 15
# define WIDTH 16

# define STACK_SIZE 4096

typedef enum 		e_states
{
	START_STATE = 0,
	CHAR_STATE,
	NUMBER_STATE,
	BACKSLASH_STATE,
	TILDE_STATE,
	DOLLAR_STATE,
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
	PIPE_V_STATE,
	SPACE_V_STATE,
	LEFT_REDIRECTION_V_STATE,
	RIGHT_REDIRECTION_V_STATE,
	LEFT_AGGREGATION_V_STATE,
	RIGHT_AGGREGATION_V_STATE,
	STAR_STATE,
	NONE_STATE
}					t_states;

typedef enum 		e_index
{
	CHAR_INDEX = 0,
	NUMBER_INDEX,
	SPACES_INDEX,
	DASH_INDEX,
	BACKSLASH_INDEX,
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
}					t_index;

typedef enum 		e_token_types
{
	WORD_TYPE = 0,
	NUMBER_TYPE,
	PIPE_TYPE,
	DOTCOMMA_TYPE,
	REDIRECTION_TYPE,
	AGGREGATION_TYPE,
	TILDE_TYPE,
	REDIRECTION_ARG_TYPE,
	AGGREGATION_ARG_TYPE,
	D_QUOTE_TYPE,
	S_QUOTE_TYPE,
	COMMAND_TYPE,
	NONE_TYPE
}					t_tokens_types;

typedef struct	s_token
{
		char	*token;
		int		type;
		char 	**tab;
}				t_token;

int lexer(char *line, t_list **tokens_list);
int 	first_check_tokens_list(t_list *lst);
int 	build_command_token(t_list *lst);
void 	delete_list_tokens(t_list **tokens_list);

int					replace_tilde(char **str);
void				put_str_in_stack(char (*stack)[STACK_SIZE], char *str);
void				put_char_in_stack(char (*stack)[STACK_SIZE], char c);
int					is_acceptor(int state);
int					is_ignored(int current, int state);
int					get_index_from_char(char *s, int i);
char	*get_dollar(char *line, int *i, int state, int A[HEIGHT][WIDTH]);
int 	build_command_token(t_list *lst);
void 	free_token(void *content, size_t size);
int					get_type_of_token(int next_state, int last_state);
int 	create_token(char *token, int n_state, int l_state, t_token **t);
int 	first_check_tokens_list(t_list *lst);
void 	delete_list_tokens(t_list **tokens_list);

#endif
