/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 22:00:59 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/20 22:24:44 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
**	Push str in a stack
*/

void	put_str_in_stack(char (*stack)[STACK_SIZE], char *str)
{
	if (((int)ft_strlen(*stack) + (int)ft_strlen(str)) >= (STACK_SIZE - 2))
	{
		ft_printf("Stack depassee!");
		exit(0);
	}
	ft_strcat(*stack, str);
}

/*
**	Push char in a stack
*/

void	put_char_in_stack(char (*stack)[STACK_SIZE], char c)
{
	if ((int)ft_strlen(*stack) >= (STACK_SIZE - 2))
	{
		ft_printf("Stack depassee!");
		exit(0);
	}
	(*stack)[ft_strlen(*stack)] = c;
}
