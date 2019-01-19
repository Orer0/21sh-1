/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 16:38:10 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/19 04:16:02 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "21sh.h"

typedef enum 		e_states
{
	START_STATE = 0,
	CHAR_STATE,
	NUMBER_STATE,
	BACKSLASH_STATE,
	TILDE_STATE,
	PIPE_STATE,
	IGNORE_SPACE_PIPE_STATE,
	IGNORE_SPACE_STATE,
	D_QUOTE_STATE,
	S_QUOTE_STATE,
	END_D_QUOTE_STATE,
	END_S_QUOTE_STATE,
	CHAR_D_QUOTE_STATE,
	BACKSLASH_D_QUOTE_STATE,
	CHAR_S_QUOTE_STATE,
	LEFT_REDIRECTION_STATE,
	RIGHT_REDIRECTION_STATE,
	IGNORE_SPACE_REDIRECTION_STATE,
	DOUBLE_LEFT_REDIRECTION_STATE,
	DOUBLE_RIGHT_REDIRECTION_STATE,
	LEFT_AGGREGATION_STATE,
	RIGHT_AGGREGATION_STATE,
	LEFT_AGGREGATION_NUMBER_STATE,
	RIGHT_AGGREGATION_NUMBER_STATE,
	RIGHT_AGGREGATION_DASH_STATE,
	DOTCOMMA_V_STATE,
	SPACE_V_STATE,
	LEFT_REDIRECTION_V_STATE,
	RIGHT_REDIRECTION_V_STATE,
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
	DOTCOMMA_INDEX,
	PIPE_INDEX,
	D_QUOTE_INDEX,
	S_QUOTE_INDEX,
	LEFT_REDIRECTION_INDEX,
	RIGHT_REDIRECTION_INDEX,
	AMPERSAND_INDEX,
	NONE_INDEX
}					t_index;

typedef struct	s_token
{
		char	*token;
		int		type;
}				t_token;

#endif
