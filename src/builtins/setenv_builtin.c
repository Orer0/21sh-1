/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 21:03:19 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/29 08:13:09 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		setenv_builtin(char **args)
{
	int		i;
	t_shell_data 	*data;

	data = shell_data_singleton();
	if (args[1])
		change_env_var(&data->env_lst, args[1], args[2]);
	else
	{
		i = -1;
		while (data->env_tab[++i])
			ft_printf("%s\n", data->env_tab[i]);
	}
	return (EXIT_SUCCESS);
}
