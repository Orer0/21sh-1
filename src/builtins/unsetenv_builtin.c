/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 21:07:14 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/29 08:13:42 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		unsetenv_builtin(char **args)
{
	t_shell_data 	*data;

	data = shell_data_singleton();
	if (args[1])
		remove_env_var(&data->env_lst, args[1]);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
