/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 22:32:06 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/11 22:38:25 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		unsetenv_builtin(char **args)
{
	t_shell_data	*data;
	int				i;

	data = shell_data_singleton();
	if (args[0])
	{
		i = -1;
		while (args[++i])
			remove_env_var(&data->env_lst, args[i]);
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
