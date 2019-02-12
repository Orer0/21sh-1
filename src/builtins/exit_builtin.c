/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 16:26:48 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/29 07:58:44 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		exit_builtin(char **args)
{
	ft_strtab_del(&args);
	if (args && args[0])
		quit_shell(ft_atoi(args[0]), 0);
	else
		quit_shell(EXIT_SUCCESS, 0);
}
