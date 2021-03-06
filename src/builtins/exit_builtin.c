/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 16:26:48 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/20 23:24:22 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		exit_builtin(char **args)
{
	int		ret;

	if (args && args[1])
	{
		ret = ft_atoi(args[1]);
		ft_strtab_del(&args);
		quit_shell(ret, 0);
	}
	else
	{
		ft_strtab_del(&args);
		quit_shell(EXIT_SUCCESS, 0);
	}
}
