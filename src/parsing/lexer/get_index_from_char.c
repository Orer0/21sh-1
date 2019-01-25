/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_index_from_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 23:31:22 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/25 03:22:16 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	get_index_from_char_2(char *s, int i)
{
	if (s[i] == '>' && s[i + 1])
		return (RIGHT_REDIRECTION_INDEX);
	else if (s[i] == '&')
		return (AMPERSAND_INDEX);
	else if (s[i] == '$')
		return (DOLLAR_INDEX);
	else if (ft_isspace(s[i]))
		return (SPACES_INDEX);
	else if (ft_isdigit(s[i]))
		return (NUMBER_INDEX);
	else if (ft_isgraph(s[i]) && s[i] != '-' && s[i] != '~' && s[i] != ';'
		&& s[i] != '|' && s[i] != '"' && s[i] != '\'' && s[i] != '<'
		&& s[i] != '>' && s[i] != '&' && s[i] != '\\')
		return (CHAR_INDEX);
	return (NONE_INDEX);
}

/*
**	Retourne l'index de la colonne du tableau automate correspondant au caractere
*/

int get_index_from_char(t_line *line)
{
	int i;
	char *s;

	s = line->line;
	i = line->i;
	if (s[i] == '-')
		return (DASH_INDEX);
	else if (s[i] == '~')
		return (TILDE_INDEX);
	else if (s[i] == ';')
		return (DOTCOMMA_INDEX);
	else if (s[i] == '=')
		return (EQUAL_INDEX);
	else if (s[i] == '|')
		return (PIPE_INDEX);
	else if (s[i] == '"')
		return (D_QUOTE_INDEX);
	else if (s[i] == '\'')
		return (S_QUOTE_INDEX);
	else if (s[i] == '\\')
		return (BACKSLASH_INDEX);
	else if (s[i] == '<' && s[i + 1])
		return (LEFT_REDIRECTION_INDEX);
	return (get_index_from_char_2(s, i));
}
