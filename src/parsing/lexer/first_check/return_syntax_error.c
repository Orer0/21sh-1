/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_syntax_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 23:38:42 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/10 23:38:59 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int				return_syntax_error(char *str)
{
	ft_fd_printf(2, "21sh: syntax error near unexpected token : \"%s\"\n", str);
	return (FALSE);
}
