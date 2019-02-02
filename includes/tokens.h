/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 02:53:42 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/02 21:14:36 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "libft.h"
# include "libftprintf.h"

/*
**	Tokens structures
*/

typedef struct	s_var
{
	char		*name;
	char		*value;
	int			value_is_expansion;
} 				t_var;

typedef struct	s_token
{
	char		*token;
	int			type;
	int			is_expansion;
}				t_token;

typedef struct	s_var_token
{
	char		*token;
	int			type;
	int			is_expansion;
	t_list		*var_lst;
}				t_var_token;

typedef	struct	s_cmd_token
{
	char		*token;
	int			type;
	int			is_expansion;
	t_var_token	**var_token;
	t_list		*args;
}				t_cmd_token;

/*
**	Tokens types
*/

typedef enum 	e_token_types
{
	START_TYPE = 0,
	WORD_TYPE,
	NUMBER_TYPE,
	PIPE_TYPE,
	VAR_TYPE,
	DOTCOMMA_TYPE,
	REDIRECTION_TYPE,
	AGGREGATION_TYPE,
	IN_RDIR_TYPE,
	OUT_RDIR_TYPE,
	OUT_ARDIR_TYPE,
	HEREDOC_TYPE,
	DUP_IN_FD_TYPE,
	DUP_OUT_FD_TYPE,
	TILDE_TYPE,
	REDIRECTION_ARG_TYPE,
	AGGREGATION_ARG_TYPE,
	D_QUOTE_TYPE,
	S_QUOTE_TYPE,
	CMD_TYPE,
	AND_TYPE,
	OR_TYPE,
	NONE_TYPE
}				t_tokens_types;

/*
**	TOKENS functions
*/

int				replace_tilde(char **str);

t_var_token 	*get_var_token_in_cmd_token(void *token);
void			set_var_token_in_cmd_token(void *token, void *var);
t_list 			*get_var_list_in_cmd_token(void *token);
t_list 			*get_var_list_token(void *token);
void 			set_var_list_token(void *token, t_list *vars);
int 			get_expansion_token(void *token);
void 			set_expansion_token(void *token, int expansion);
int 			get_type_token(void *token);
void 			set_type_token(void *token, int type);
char 			*get_token_token(void *token);
void 			set_token_token(void *token, char *str);
void 			set_args_token(void *token, t_list *tab);
t_list 			*get_args_token(void *token);
int				is_redirection(int type);
int				is_aggregation(int type);
int				is_operator(int type);
int				type_cmp(int first, int second);
char 			**get_cmd_tab(t_cmd_token *token);
char 			**get_var_tab_for_unset(t_var_token *token);
char 			**get_var_tab(t_var_token *token);


#endif
