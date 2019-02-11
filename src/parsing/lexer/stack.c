/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 22:00:59 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/11 00:27:48 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
**	Push str in a stack
*/

int		put_str_in_stack(char (*stack)[STACK], char *str)
{
	if (((int)ft_strlen(*stack) + (int)ft_strlen(str)) >= (STACK - 2))
	{
		ft_fd_printf(2, "21sh: argument too long\n");
		return (FALSE);
	}
	ft_strcat(*stack, str);
	return (TRUE);
}

/*
**	Push char in a stack
*/

int		put_char_in_stack(char (*stack)[STACK], char c)
{
	if ((int)ft_strlen(*stack) >= (STACK - 2))
	{
		ft_fd_printf(2, "21sh: argument too long\n");
		return (FALSE);
	}
	(*stack)[ft_strlen(*stack)] = c;
	return (TRUE);
}
