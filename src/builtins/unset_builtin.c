/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 21:07:14 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/31 04:38:54 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		unset_builtin(char **args)
{
	t_shell_data 	*data;
	int				i;

	data = shell_data_singleton();
	if (args[0])
	{
		i = -1;
		while (args[++i])
		{
			remove_env_var(&data->intern_env_lst, args[i]);
			remove_env_var(&data->env_lst, args[i]);
		}
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
