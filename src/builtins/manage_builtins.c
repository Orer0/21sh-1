/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:58:16 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/31 04:38:25 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void			reset_env_tab(void)
{
	t_shell_data	*data;

	data = shell_data_singleton();
	ft_strtab_del(&data->env_tab);
	if (!env_lst_to_tab(&data->env_lst, &data->env_tab))
		quit_shell(EXIT_FAILURE, MALLOC_ERR);
}

int					manage_builtins(char **command)
{
	t_shell_data	*data;

	data = shell_data_singleton();
	if (ft_strequ(command[0], "exit"))
		exit_builtin(command);
	else if (ft_strequ(command[0], "cd"))
	{
		data->last_status = cd_builtin(command);
		reset_env_tab();
	}
	else if (ft_strequ(command[0], "set"))
	{
		data->last_status = set_builtin(&command[1]);
		reset_env_tab();
	}
	else if (ft_strequ(command[0], "export"))
	{
		data->last_status = export_builtin(&command[1]);
		reset_env_tab();
	}
	else if (ft_strequ(command[0], "unset"))
	{
		data->last_status = unset_builtin(&command[1]);
		reset_env_tab();
	}
	else if (ft_strequ(command[0], "echo"))
		data->last_status = echo_builtin(command);
	else
		return (FALSE);
	return (TRUE);
}
