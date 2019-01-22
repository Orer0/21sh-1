/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 02:53:42 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/22 03:58:16 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "libft.h"
# include "libftprintf.h"

/*
**	Tokens structures
*/

typedef struct	s_token
{
	char		*token;
	int			type;
}				t_token;

typedef	struct	s_cmd_token
{
	char		*token;
	int			type;
	char 		**tab;
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
	NONE_TYPE
}				t_tokens_types;

/*
**	TOKENS functions
*/

int 			get_type_token(t_list *lst);
void 			set_type_token(t_list *lst, int type);
char 			*get_token_token(t_list *lst);
void 			set_tab_token(t_list *lst, char **tab);
char 			**get_tab_token(t_list *lst);
int				is_redirection(int type);
int				is_aggregation(int type);
int				type_cmp(int first, int second);		

#endif
